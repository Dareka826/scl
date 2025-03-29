#include <stdio.h>  /* FILE fopen() fclose() fwrite() fputc() fputs() sprintf() */
#include <stdlib.h> /* exit() EXIT_FAILURE */
#include <stddef.h> /* NULL */
#include <string.h> /* strlen() */
#include <limits.h> /* CHAR_BIT */
#include "assert.h" /* _assert() */


/* Count the number of bits that can fit in a given type without relying on
 * bit shifting or -1 (not sure if they behave the same on all platforms) */
#define numbits(int_type, out_var_ptr) \
    do { \
        unsigned int_type x = 0, old_x; \
        *(out_var_ptr) = 0; \
        \
        while (1) { \
            old_x = x; \
            x = (x * 2) + 1; \
            if (x <= old_x) break; \
            *(out_var_ptr) += 1; \
        } \
    } while (0)

#define MAX_LINE_LEN 254

typedef unsigned long ulong;

enum {
    STATUS_OK = 0,
    ERR_OPEN  = 1,
    ERR_CLOSE = 2,
    ERR_WRITE = 4
};

void _fwrite(FILE* file, char *buf, size_t count, int *err) {
    size_t written_count;

    written_count = fwrite(buf, 1, count, file);
    if (written_count != count)
        *err |= ERR_WRITE;
}

#define WRITE_CHR(file, chr, p_err) \
    do { \
        if (fputc((chr), (file)) != (chr)) \
            *(p_err) |= ERR_WRITE; \
    } while(0)

#define WRITE_STR(file, str, p_err) \
    _fwrite((file), (str), strlen((str)), (p_err))

enum {
    SIZE_ID_CHAR        = 0,
    SIZE_ID_SHORT       = 1,
    SIZE_ID_INT         = 2,
    SIZE_ID_LONG        = 3,
    SIZE_ID_FLOAT       = 4,
    SIZE_ID_DOUBLE      = 5,
    SIZE_ID_LONG_DOUBLE = 6,
    SIZE_ID_POINTER     = 7,

    SIZE_ID_ELEM_COUNT
};


int main(void) {
    char buf[MAX_LINE_LEN + 1];
    int char_count = 0, err = 0;

    ulong  bits[SIZE_ID_ELEM_COUNT];
    ulong bytes[SIZE_ID_ELEM_COUNT];
    ulong bpb = 0; /* bits per byte */

    /* Check for sane char
     * Any C89 conformant system should meet these */
    numbits(char,  &(bits[SIZE_ID_CHAR]));
    _assert(bits[SIZE_ID_CHAR] >= 8);

    bytes[SIZE_ID_CHAR] = sizeof(char);
    _assert(bytes[SIZE_ID_CHAR] == 1);

    /* The char type should represent host's byte
     * CHAR_BIT is bits per byte */
    bpb = bits[SIZE_ID_CHAR];
    _assert(CHAR_BIT == bpb);

    /* Detect other sizes */
    numbits(short, &(bits[SIZE_ID_SHORT]));
    bytes[SIZE_ID_SHORT] = sizeof(short);

    numbits(int,   &(bits[SIZE_ID_INT]));
    bytes[SIZE_ID_INT] = sizeof(int);

    numbits(long,  &(bits[SIZE_ID_LONG]));
    bytes[SIZE_ID_LONG] = sizeof(long);

    bytes[SIZE_ID_FLOAT] = sizeof(float);
    bits[SIZE_ID_FLOAT]  = bytes[SIZE_ID_FLOAT] * bits[SIZE_ID_CHAR];

    bytes[SIZE_ID_DOUBLE] = sizeof(double);
    bits[SIZE_ID_DOUBLE]  = bytes[SIZE_ID_DOUBLE] * bits[SIZE_ID_CHAR];

    bytes[SIZE_ID_LONG_DOUBLE] = sizeof(long double);
    bits[SIZE_ID_LONG_DOUBLE]  = bytes[SIZE_ID_LONG_DOUBLE] * bits[SIZE_ID_CHAR];

    bytes[SIZE_ID_POINTER] = sizeof(void*);
    bits[SIZE_ID_POINTER]  = bytes[SIZE_ID_POINTER] * bits[SIZE_ID_CHAR];

    {
        FILE *f_sizes = NULL;
        f_sizes = fopen("./gen_sizes.h", "w");
        if (f_sizes == NULL) exit(ERR_OPEN);

        err = STATUS_OK;

        WRITE_STR(f_sizes, "#ifndef __SCL_GEN_SIZES_H_S4GP259L\n", &err);
        WRITE_STR(f_sizes, "#define __SCL_GEN_SIZES_H_S4GP259L\n", &err);

        WRITE_CHR(f_sizes, '\n', &err);

        char_count = sprintf(buf, "#define CHAR_BYTES       %lu\n", bytes[SIZE_ID_CHAR]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define SHORT_BYTES      %lu\n", bytes[SIZE_ID_SHORT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define INT_BYTES        %lu\n", bytes[SIZE_ID_INT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define LONG_BYTES       %lu\n", bytes[SIZE_ID_LONG]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define FLOAT_BYTES      %lu\n", bytes[SIZE_ID_FLOAT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define DOUBLE_BYTES     %lu\n", bytes[SIZE_ID_DOUBLE]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define LDOUBLE_BYTES    %lu\n", bytes[SIZE_ID_LONG_DOUBLE]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define PTR_BYTES        %lu\n", bytes[SIZE_ID_POINTER]);
        _fwrite(f_sizes, buf, char_count, &err);

        WRITE_CHR(f_sizes, '\n', &err);

        char_count = sprintf(buf, "#define CHAR_BITS        %lu\n", bits[SIZE_ID_POINTER]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define SHORT_BITS       %lu\n", bits[SIZE_ID_SHORT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define INT_BITS         %lu\n", bits[SIZE_ID_INT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define LONG_BITS        %lu\n", bits[SIZE_ID_LONG]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define FLOAT_BITS       %lu\n", bits[SIZE_ID_FLOAT]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define DOUBLE_BITS      %lu\n", bits[SIZE_ID_DOUBLE]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define LDOUBLE_BITS     %lu\n", bits[SIZE_ID_LONG_DOUBLE]);
        _fwrite(f_sizes, buf, char_count, &err);
        char_count = sprintf(buf, "#define PTR_BITS         %lu\n", bits[SIZE_ID_POINTER]);
        _fwrite(f_sizes, buf, char_count, &err);

        WRITE_CHR(f_sizes, '\n', &err);

        WRITE_STR(f_sizes, "#endif\n", &err);

        if(fclose(f_sizes) != 0) err |= ERR_CLOSE;
        f_sizes = NULL;

        if(err != STATUS_OK)
            exit(err);
    }

    {
        FILE *f_types = NULL;
        f_types = fopen("./gen_types.h", "w");
        if (f_types == NULL) exit(ERR_OPEN);

        err = STATUS_OK;

        WRITE_STR(f_types, "#ifndef __SCL_GEN_TYPES_H_2wHhbHlF\n", &err);
        WRITE_STR(f_types, "#define __SCL_GEN_TYPES_H_2wHhbHlF\n", &err);

        WRITE_CHR(f_types, '\n', &err);

        /* char  is at least 8 bits (should always be 8?)
         * short is at least 16 bits
         * int   is at least 16 bits
         * long  is at least 32 bits */

        /*
         * u8p  -> unsigned 8+  -> at least  8 bits (can be more)
         * u16p -> unsigned 16+ -> at least 16 bits (can be more)
         */

        WRITE_STR(f_types, "typedef unsigned char  ubyte;\n", &err);
        WRITE_STR(f_types, "typedef   signed char  ibyte;\n", &err);
        WRITE_STR(f_types, "typedef unsigned char  u8p;\n", &err);
        WRITE_STR(f_types, "typedef   signed char  i8p;\n", &err);

        if (bits[SIZE_ID_CHAR] >= 16) {
            WRITE_STR(f_types, "typedef unsigned char  u16p;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i16p;\n", &err);
        } else if (bits[SIZE_ID_SHORT] >= 16) {
            WRITE_STR(f_types, "typedef unsigned short u16p;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i16p;\n", &err);
        }

        if (bits[SIZE_ID_CHAR] >= 32) {
            WRITE_STR(f_types, "typedef unsigned char  u32p;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i32p;\n", &err);
        } else if (bits[SIZE_ID_SHORT] >= 32) {
            WRITE_STR(f_types, "typedef unsigned short u32p;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i32p;\n", &err);
        } else if (bits[SIZE_ID_INT] >= 32) {
            WRITE_STR(f_types, "typedef unsigned int   u32p;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i32p;\n", &err);
        } else if (bits[SIZE_ID_LONG] >= 32) {
            WRITE_STR(f_types, "typedef unsigned long  u32p;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i32p;\n", &err);
        }

        if (bits[SIZE_ID_CHAR] >= 64) {
            WRITE_STR(f_types, "typedef unsigned char  u64p;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i64p;\n", &err);
        } else if (bits[SIZE_ID_SHORT] >= 64) {
            WRITE_STR(f_types, "typedef unsigned short u64p;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i64p;\n", &err);
        } else if (bits[SIZE_ID_INT] >= 64) {
            WRITE_STR(f_types, "typedef unsigned int   u64p;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i64p;\n", &err);
        } else if (bits[SIZE_ID_LONG] >= 64) {
            WRITE_STR(f_types, "typedef unsigned long  u64p;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i64p;\n", &err);
        }

        if (bits[SIZE_ID_CHAR] >= 128) {
            WRITE_STR(f_types, "typedef unsigned char  u128p;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i128p;\n", &err);
        } else if (bits[SIZE_ID_SHORT] >= 128) {
            WRITE_STR(f_types, "typedef unsigned short u128p;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i128p;\n", &err);
        } else if (bits[SIZE_ID_INT] >= 128) {
            WRITE_STR(f_types, "typedef unsigned int   u128p;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i128p;\n", &err);
        } else if (bits[SIZE_ID_LONG] >= 128) {
            WRITE_STR(f_types, "typedef unsigned long  u128p;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i128p;\n", &err);
        }

        WRITE_CHR(f_types, '\n', &err);

        if (bytes[SIZE_ID_POINTER] == bytes[SIZE_ID_LONG]) {
            WRITE_STR(f_types, "typedef unsigned long usize;\n", &err);
            WRITE_STR(f_types, "typedef   signed long isize;\n", &err);
        } else if (bytes[SIZE_ID_POINTER] == bytes[SIZE_ID_INT]) {
            WRITE_STR(f_types, "typedef unsigned int usize;\n", &err);
            WRITE_STR(f_types, "typedef   signed int isize;\n", &err);
        } else if (bytes[SIZE_ID_POINTER] == bytes[SIZE_ID_SHORT]) {
            WRITE_STR(f_types, "typedef unsigned short usize;\n", &err);
            WRITE_STR(f_types, "typedef   signed short isize;\n", &err);
        } else if (bytes[SIZE_ID_POINTER] == bytes[SIZE_ID_CHAR]) {
            WRITE_STR(f_types, "typedef unsigned char usize;\n", &err);
            WRITE_STR(f_types, "typedef   signed char isize;\n", &err);
        } else {
            fputs("[E]: Pointer type size doesn't match any int type!\n", stderr);
            return EXIT_FAILURE;
        }

        WRITE_CHR(f_types, '\n', &err);

        WRITE_STR(f_types, "#endif\n", &err);

        if(fclose(f_types) != 0) err |= ERR_CLOSE;
        f_types = NULL;

        if(err != STATUS_OK)
            exit(err);
    }

    return EXIT_SUCCESS;
}
