#!/bin/zsh

# Find and delete all files with a .tmp extension
find . -type f -name "*.tmp" -exec rm -v {} \;

