#!/bin/zsh

# List all files in the current directory with their sizes
for file in *; do
    if [ -f "$file" ]; then
        size=$(stat -c%s "$file")
        echo "$file: $size bytes"
    fi
done

