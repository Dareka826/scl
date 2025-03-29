#!/bin/sh
set -eu

for SIZE in "$@"; do
    if ! { printf '%s' "$@" | grep -E '^[1-9][0-9]*$' >/dev/null 2>&1; }; then
        continue
    fi

    sed "s|XX_SIZE_XX|${SIZE}|g" < alloc.c.in > "gen_alloc${SIZE}.c"
    sed "s|XX_SIZE_XX|${SIZE}|g" < alloc.h.in > "gen_alloc${SIZE}.h"
done
