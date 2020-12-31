#!/bin/bash
day=$(($(ls src/ -tr | grep '^day*' | tail -n1 | cut -c4-5)+1))

./setday.sh $day
mkdir src/day$day && cd $_
touch $1.txt
touch $2.c
touch makefile
touch makefile.title
echo TITLE=$2 >> makefile.title
cd ../../

mkdir include/day$day && cd $_
touch $2.h
