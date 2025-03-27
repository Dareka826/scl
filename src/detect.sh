#!/bin/sh
set -eu

CC="${CC-}"
[ -n "${CC}" ] || CC="cc"

if { ! [ -e ./gen_sizes.h ]; } || { ! [ -e ./gen_types.h ]; }; then
    ${CC} $(cat ./compile_flags.txt) -o ./tmp_detect ./detect.c
    ./tmp_detect
    rm ./tmp_detect
fi
