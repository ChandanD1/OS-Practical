#!/bin/zsh

# Iterate over all .log files in the current directory
for logfile in *.log; do
    if [ -f "$logfile" ]; then
        echo "Displaying last 20 lines of $logfile:"
        echo "--------------------------------------"
        tail -n 20 "$logfile"
        echo "--------------------------------------"
        echo
    fi
done
