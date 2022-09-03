#!/bin/bash

for f in *$1*; 
do 
	mv -i -- "$f" "${f//$1/$2}";
done
