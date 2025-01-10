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
img_list=()
for l in $LAYERS; do
    ln=$( echo "$l" | tr '[:upper:]' '[:lower:]')
    img_list+=('-label')
    img_list+=("$lindex - $l")
    img_list+=("$lindex$ln.png")
    lindex=$((lindex + 1))
done

magick montage -border 4 -tile 4x4 -mode concatenate $img_list out.png
