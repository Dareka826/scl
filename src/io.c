#include "io.h"

FILE *scl_fopen(char const *const pathname, char const *const mode, ubyte *const err) {
    FILE *ret = NULL;

    if (err != NULL) *err = SCL_IO_ERR_OK;
    ret = fopen(pathname, mode);
    if (err != NULL && ret == NULL) *err = SCL_IO_ERR_OPEN;

    return ret;
}

void _scl_fclose(FILE *stream, ubyte *const err) {
    int ret = 0;

    if (err != NULL) *err = SCL_IO_ERR_OK;
    ret = fclose(stream);
    if (err != NULL && ret != 0) *err = SCL_IO_ERR_CLOSE;
}

void scl_fwrite(FILE *const stream, ubyte const *const buf, size_t count, ubyte *const err) {
    size_t written_count;

    if (err != NULL) *err = SCL_IO_ERR_OK;
    written_count = fwrite(buf, 1, count, stream);

    if (err != NULL && (written_count != count || ferror(stream) != 0))
        *err = SCL_IO_ERR_WRITE;
}

void scl_fread( FILE *const stream, ubyte *const buf, size_t count, size_t *const read_count, ubyte *const err) {
    if (err != NULL) *err = SCL_IO_ERR_OK;

    if (read_count != NULL)
        *read_count = fread(buf, 1, count, stream);
    else fread(buf, 1, count, stream);

    if (err != NULL && ferror(stream) != 0)
        *err = SCL_IO_ERR_READ;
}
