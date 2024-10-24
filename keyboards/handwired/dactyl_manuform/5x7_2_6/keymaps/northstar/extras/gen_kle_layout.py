#!/usr/bin/python3

import json
import argparse


def parse_json_file(file_path, expected_type):
    try:
        with open(file_path, 'r') as file:
            data = json.load(file)
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


def update_keys(kle_template, layer_it):
    result = []
    for row in kle_template:
        if isinstance(row, list):
            kle_row = []
            for obj in row:
                if isinstance(obj, str):
                    kle_row.append(str(next(layer_it)))
                else:
                    kle_row.append(obj)
            result.append(kle_row)
        else:
            result.append(row)
    return result


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

    # Parse arguments
    args = vars(parser.parse_args())

    # Parse the file as JSON
    keymap = parse_json_file(args['keymap-json-file'], dict)
    kle_template = parse_json_file(args['kle-template-file'], list)

    layer = keymap["layers"][args['layer-index']]

    layer_it = iter(layer)

    kle_result = update_keys(kle_template, layer_it)

    print(json.dumps(kle_result))


if __name__ == "__main__":
    main()
