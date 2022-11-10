#!/bin/bash

executable=$1
folder=$2
count="0"
if [ ! -f "$executable" ]; then
	ls -1 "$folder" | wc -l
else
	for f in "$folder"/*
	do
		if [ "$f" -nt "$executable" ]; then
			# echo $f
			((++count))
		fi
	done;
echo $count
fi;