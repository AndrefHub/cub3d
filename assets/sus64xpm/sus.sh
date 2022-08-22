#!/bin/bash
for i in {1..5}
do
    convert 'sus64-'"$i"'.xpm' -scale 32x32 'sus32-'"$i"'.xpm'
done
