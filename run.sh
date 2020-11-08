#!/bin/bash

g++ src/* -o main -Iinc/

mkdir output

for path in data-mtcarp/* ;
    do
        filename="${path##*/}"
        filename="${filename%.*}"
        echo ./main $path output/$filename.out
        ./main $path > output/$filename.out

    done

rm main