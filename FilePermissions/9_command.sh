#!/bin/zsh

# Iterate over all .txt files in the current directory
for txtfile in *.txt; do
    if [ -f "$txtfile" ]; then
        bakfile="${txtfile%.txt}.bak"
        mv -v "$txtfile" "$bakfile"
    fi
done

