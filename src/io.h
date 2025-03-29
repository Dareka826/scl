#ifndef __SCL_IO_H_NGbj8lln
#define __SCL_IO_H_NGbj8lln

#include "types.h"
#include <stdio.h>

enum {
    SCL_IO_ERR_OK = 0,

    SCL_IO_ERR_OPEN  = 1 << 0,
    SCL_IO_ERR_CLOSE = 1 << 1,
    SCL_IO_ERR_WRITE = 1 << 2,
    SCL_IO_ERR_READ  = 1 << 3
};

FILE *scl_fopen(char const *const pathname, char const *const mode, ubyte *const err);
void _scl_fclose(FILE *stream, ubyte *const err);
#define scl_fclose(stream, err) do { _scl_fclose((stream), (err)); (stream) = NULL; } while (0)

void scl_fwrite(FILE *const stream, ubyte const *const buf, size_t count, ubyte *const err);
void scl_fread( FILE *const stream, ubyte *const buf, size_t count, size_t *const read_count, ubyte *const err);

#endif
