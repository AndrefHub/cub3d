#!/bin/bash

for file in *.c; do
	echo '//' "$file" '//' >> prototypes.h
	echo >> prototypes.h
	ctags -x "$file" >> prototypes.h
	echo >> prototypes.h
done
