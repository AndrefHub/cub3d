#!/bin/bash
echo '#ifndef PROTOTYPES_H' > prototypes.h
echo '# define PROTOTYPES_H' >> prototypes.h
echo >> prototypes.h
for file in *.c; do
	echo '//' "$file" '//' >> prototypes.h
	echo >> prototypes.h
	ctags -o - --kinds-C=f --kinds-C++=f -x --_xformat='%{typeref}	%{name}%{signature};' "$file" | tr ':' ' ' | sed -e 's/^typename //' >> prototypes.h
	echo >> prototypes.h
done
echo '#endif' >> prototypes.h

