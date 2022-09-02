#!/bin/bash

for f in *$1*; 
do 
	echo mv -i -- "$f" "${f//$1/$2}"; 
done
