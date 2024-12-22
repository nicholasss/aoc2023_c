#! /bin/bash

# build for aoc2023

rm -r "./build/$1.o"

clang "./source/$1.c" -Wall -Wextra -Wconversion -Wno-sign-conversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -o "./build/$1.o"

"./build/$1.o"
