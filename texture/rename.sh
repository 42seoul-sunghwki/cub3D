#!/bin/bash

i=1;
path="dancing_bear"

for png_file in "$path"/*.xpm; do
    if [ -f "$png_file" ]; then
		mv "$png_file" "$path"/"$i.xpm"
	fi
	i=$((i + 1))
done