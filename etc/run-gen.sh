#!/bin/bash

g++ instance-gen.cpp

mkdir data

for path in $1* ;
	do
		filename="${path##*/}"
		filename="${filename%.*}"
		
		./a.out $path data/$filename.mtcarp
	done

rm a.out
