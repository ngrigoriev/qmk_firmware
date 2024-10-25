This is a simple tool to generate the JSON file that can be uploaded to https://keyboard-layout-editor.com (KLE).

Note: the JSON needs to be *uploaded* and not pasted as Raw Data. It seems Raw Data does not accept the keyboard metadata object.


How to use:

    - generate the JSON file for your keymap: "qmk c2json --no-cpp > layers.json". Note --no-cpp, this actually allows you to preserve your own key codes as-is. It is assumed that you will want to define your own labels for them.
    - edit override_dict.tsv (space-separated: keycode<SPACE>label). The label can contain ":" which will be translated into \n. Seel KLE documentation about 12 different key label positions separated by \n.
    - Run "python3 gen_kle_layout.py --qmk-firmware-root /home/you/git/qmk-firmware/data/constants/keycodes --dict override_dict.tsv layers.json KLE.json <layer-number>  > ~/layout.json"
    - Upload layout.json to KLE website


