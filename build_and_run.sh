#! /bin/bash

OUT="$(basename $1 .c)"
clang -Wall -Werror "$1" -o "build/$OUT" && "build/$OUT"
