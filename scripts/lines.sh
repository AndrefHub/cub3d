#!/bin/bash

lines=0
directories="."
if [ $# -ne 0 ]
    then
        directories="$@"
fi

for dir in $directories; do
    for f in "$dir/"*; do
        if [ -f "$f" ]
            then
                wc=$(< "$f" wc -l)
                lines=$((lines + wc))
        fi
    done;
done;

echo $lines
