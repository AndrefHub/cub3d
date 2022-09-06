#!/bin/bash
for i in $(seq 733 755);
do
	~/homebrew/bin/convert 'wah'"$i"'.png' 'wah'"$i"'.xpm';
done
