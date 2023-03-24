#!/bin/bash

lines=0
directories="."
header42=0
if [ $# -ne 0 ]
then
    directories="$@"
    for f in $directories; do
        echo "'$f'"
        if [ "$f" == '--ignore-headers' ]
        then
            header42=12
        fi
    done;
fi

for dir in $directories; do
    if [[ "$dir" != '--'* ]]
    then
        for f in "$dir/"*; do
            if [ -f "$f" ]
            then
                wc=$(< "$f" wc -l)
                lines=$((lines + wc - header42))
            fi
        done;
    fi
done;

echo $lines
