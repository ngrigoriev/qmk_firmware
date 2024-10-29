#!/usr/bin/python3

import json
import commentjson
import argparse
import csv
import os
import jq
from datetime import timedelta
from requests_cache import CachedSession


def parse_json_file(file_path, expected_type):
    try:
        with open(file_path, 'r') as file:
            data = commentjson.load(file)
            if isinstance(data, expected_type):
                return data
            else:
                print("The JSON content is wrong"
                      " (check template and QMK JSON syntax)")
                return None
    except json.JSONDecodeError:
        print("Error: The file is not valid JSON.")
    except FileNotFoundError:
        print(f"Error: The file '{file_path}' was not found.")


def make_label(kc, kc_dict):
    dw = kc_dict.get(kc)
    if dw:
        return dw
    return kc


def update_keys(kle_template, layer_it, kc_dict):
    result = []
    for row in kle_template:
        if isinstance(row, list):
            kle_row = []
            for obj in row:
                if isinstance(obj, str):
                    kc = str(next(layer_it))
                    kle_row.append(make_label(kc, kc_dict))
                else:
                    kle_row.append(obj)
            result.append(kle_row)
        else:
            result.append(row)
    return result


def load_qmk_keycodes_api(kc_dict):
    jq_index_prog = jq.compile('.constants | to_entries | map({version: .value | .[], file: .key}) | .[] | "/" + .file + "_" + .version + ".json" ')
    jq_prog = jq.compile('(.keycodes // {}) + (.aliases // {}) | to_entries | [.[] | select (.value | type == "object")] | map({key: .value.key, label: .value.label, aliases: (.value.aliases + [.value.key] // [.value.key])}) | map({alias: .aliases | .[], label: .label}) | .[]')

    API_URL = "https://keyboards.qmk.fm/v1"
    API_METADATA_URL = API_URL + "/constants_metadata.json"

    session = CachedSession(
        'qmk_api_cache',
        use_cache_dir=True,
        cache_control=True,
        expire_after=timedelta(days=1),
        allowable_codes=[200],
        allowable_methods=['GET'],
        stale_if_error=True,
    )

    md_resp = session.get(API_METADATA_URL)
    assert md_resp.status_code == 200
    all_kc_paths = jq_index_prog.input_value(json.loads(md_resp.text)).all()

    for kc_path in all_kc_paths:
        kc_resp = session.get(API_URL + "/constants" + kc_path)
        assert kc_resp.status_code == 200
        qmk_dict_transfomed = jq_prog.input_value(json.loads(kc_resp.text))
        for qmk_kc in iter(qmk_dict_transfomed):
            if 'label' in qmk_kc:
                kc_dict[qmk_kc['alias']] = "\n\n\n\n\n\n\n\n\n" + str(qmk_kc['label']) + "\n\n"

    return kc_dict


def load_custom_dict(dict_file, kc_dict):
    with open(dict_file) as dfd:
        for row in dfd:
            kc, label = row.split(" ", 1)
            if label.count(':') == 0:
                label = "\n\n\n\n\n\n\n\n\n" + label + "\n\n"
            kc_dict[kc] = label.replace(":", "\n")
    return kc_dict


def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(
            description="Generate KLE (keyboard-layout-editor.com)"
            "layout from QMK keymap")
    parser.add_argument('keymap-json-file', type=str,
                        help='Path to the keymap JSON file (qmk c2json)')
    parser.add_argument('kle-template-file', type=str,
                        help='Path to the keymap KLE template JSON file')
    parser.add_argument('layer-index', type=int,
                        help='Name of the QMK layer to use (0-based)')
    parser.add_argument('-d', '--dict',
                        help='Additional dictionary file to use (see dict-sample.json')

    # Parse arguments
    args = vars(parser.parse_args())

    # Parse the file as JSON
    keymap = parse_json_file(args['keymap-json-file'], dict)
    kle_template = parse_json_file(args['kle-template-file'], list)

    layer = keymap["layers"][args['layer-index']]

    layer_it = iter(layer)

    kc_dict = {}

    load_qmk_keycodes_api(kc_dict)

    if args['dict']:
        load_custom_dict(args['dict'], kc_dict)

    kle_result = update_keys(kle_template, layer_it, kc_dict)

    print(json.dumps(kle_result))


if __name__ == "__main__":
    main()
