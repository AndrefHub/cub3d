#!/bin/bash
echo '#ifndef PROTOTYPES_H' > prototypes.h
echo '# define PROTOTYPES_H' >> prototypes.h
echo >> prototypes.h
for file in *.c; do
	echo '//' "$file" '//' >> prototypes.h
	echo >> prototypes.h
	ctags -x "$file" | awk '{printf $4 "\t"; $1=$2=$3=$4=""; $0=$0; $1=$1; print $0 ";"}' >> prototypes.h
	echo >> prototypes.h
done
echo '#endif' >> prototypes.h

