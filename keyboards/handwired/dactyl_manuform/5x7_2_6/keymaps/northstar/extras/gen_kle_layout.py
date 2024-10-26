#!/usr/bin/python3

import json
import commentjson
import argparse
import csv
import os
import jq


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


def load_qmk_keycodes(dir, kc_dict):
    jq_prog = jq.compile('.keycodes // {} | to_entries | [.[] | select (.value | type == "object")] | map({key: .value.key, label: .value.label, aliases: (.value.aliases + [.value.key] // [.value.key])}) | map({alias: .aliases | .[], label: .label}) | .[]')
    for kc_fn in os.listdir(dir):
        f = os.path.join(dir, kc_fn)
        if os.path.isfile(f) and (os.stat(f).st_size > 2):
            qmk_dict = parse_json_file(f, dict)
            qmk_dict_transfomed = jq_prog.input_value(qmk_dict)
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
    parser.add_argument("-q", "--qmk-firmware-root",
                        help='Root directory of QMK firmware source tree for reading the keycodes')

    # Parse arguments
    args = vars(parser.parse_args())

    # Parse the file as JSON
    keymap = parse_json_file(args['keymap-json-file'], dict)
    kle_template = parse_json_file(args['kle-template-file'], list)

    layer = keymap["layers"][args['layer-index']]

    layer_it = iter(layer)

    kc_dict = {}
    if args['qmk_firmware_root']:
        load_qmk_keycodes(args['qmk_firmware_root'], kc_dict)
    if args['dict']:
        load_custom_dict(args['dict'], kc_dict)

    kle_result = update_keys(kle_template, layer_it, kc_dict)

    print(json.dumps(kle_result))


if __name__ == "__main__":
    main()
