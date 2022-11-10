#!/bin/bash
dir="."
if [ $# -ne 0 ]
    then
        dir="$1"
fi

echo '#ifndef PROTOTYPES_H' > prototypes.h
echo '# define PROTOTYPES_H' >> prototypes.h
echo >> prototypes.h
for file in "$dir/"*.c; do
	echo '//' "$file" '//' >> prototypes.h
	echo >> prototypes.h
	# ctags -x "$file" | awk '{print $4}' >> prototypes.h
	
	ctags -x "$file" | awk '{if ($5!="static") {if ($5=="inline") {printf $6 "\t"; $1=$2=$3=$4=$5=$6=""; $0=$0; $1=$1; print $0 ";"} else {printf $5 "\t"; $1=$2=$3=$4=$5=""; $0=$0; $1=$1; print $0 ";"}	} }' >> prototypes.h
	# ctags -x "$file" | awk '{if ($4!="static") {if ($4=="inline") {printf $5 "\t"; $1=$2=$3=$4=$5=""; $0=$0; $1=$1; print $0 ";"} else {printf $4 "\t"; $1=$2=$3=$4=""; $0=$0; $1=$1; print $0 ";"}	} }' >> prototypes.h
	echo >> prototypes.h
done
echo '#endif' >> prototypes.h

