#!/bin/zsh

LAYERS=(\
    _BASE \
    _LOWER \
    _FN \
    _NUMBER \
    _MAGIC \
    _CURSOR \
    _SYS \
    _TYPING \
    _GAMING \
    _WORLD \
    _EMAIL \
    _SYMBOL \
    _MOUSE)

lindex=0
for l in $LAYERS; do
    echo $l
    python3 gen_kle_layout.py --keyboard-name "$lindex$l" --dict override_dict.tsv layers.json KLE.json $lindex > $lindex$l.json
    lindex=$((lindex + 1))
done
