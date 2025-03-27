#include <stdio.h>  /* FILE fopen() fclose() fwrite() fputc() fputs() sprintf() */
#include <stdlib.h> /* exit() EXIT_FAILURE */
#include <stddef.h> /* NULL */
#include <string.h> /* strlen() */

#define _assert(expr) if (!(expr)) exit(EXIT_FAILURE);
#define MAX_LINE_LEN 255

typedef unsigned int uint_t;

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

#define WRITE_CHR(file, chr, p_err) do { if (fputc((chr), (file)) != (chr)) *(p_err) |= ERR_WRITE; } while(0)
#define WRITE_STR(file, str, p_err) do { _fwrite((file), (str), strlen((str)), (p_err)); } while(0)

int main(void) {
    uint_t char_bytes = 0, short_bytes = 0, int_bytes = 0, long_bytes = 0, 
           float_bytes = 0, double_bytes = 0, long_double_bytes = 0,
           ptr_bytes = 0;
    char buf[MAX_LINE_LEN + 1];
    int char_count = 0, err = 0;

    /* Detect sizes */
    char_bytes        = sizeof(char);
    short_bytes       = sizeof(short);
    int_bytes         = sizeof(int);
    long_bytes        = sizeof(long);
    float_bytes       = sizeof(float);
    double_bytes      = sizeof(double);
    long_double_bytes = sizeof(long double);
    ptr_bytes         = sizeof(void*);

    /* Write output */
    {
        FILE *f_sizes = NULL;
        f_sizes = fopen("./gen_sizes.h", "w");
        if (f_sizes == NULL) exit(ERR_OPEN);

        err = STATUS_OK;

        WRITE_STR(f_sizes, "#ifndef __SCL_GEN_SIZES_H_S4GP259L\n", &err);
        WRITE_STR(f_sizes, "#define __SCL_GEN_SIZES_H_S4GP259L\n", &err);

        WRITE_CHR(f_sizes, '\n', &err);

        char_count = sprintf(buf, "#define CHAR_BYTES       %u\n", char_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define SHORT_BYTES      %u\n", short_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define INT_BYTES        %u\n", int_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define LONG_BYTES       %u\n", long_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define FLOAT_BYTES      %u\n", float_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define DOUBLE_BYTES     %u\n", double_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define LDOUBLE_BYTES    %u\n", long_double_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        char_count = sprintf(buf, "#define PTR_BYTES        %u\n", ptr_bytes);
        _fwrite(f_sizes, buf, char_count, &err);

        WRITE_CHR(f_sizes, '\n', &err);

        WRITE_STR(f_sizes, "#endif\n", &err);

        if(fclose(f_sizes) != 0) err |= ERR_CLOSE;
        f_sizes = NULL;

        if(err != STATUS_OK)
            exit(err);
    }

    /* Write output */
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

        /* u8_t i8_t */
        if (char_bytes == 1) {
            WRITE_STR(f_types, "typedef unsigned char  u8_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i8_t;\n", &err);
        }

        /* u16_t i16_t */
        if (char_bytes == 2) {
            WRITE_STR(f_types, "typedef unsigned char  u16_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i16_t;\n", &err);
        } else if (short_bytes == 2) {
            WRITE_STR(f_types, "typedef unsigned short u16_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i16_t;\n", &err);
        } else if (int_bytes == 2) {
            WRITE_STR(f_types, "typedef unsigned int   u16_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i16_t;\n", &err);
        }

        /* u32_t i32_t */
        if (char_bytes == 4) {
            WRITE_STR(f_types, "typedef unsigned char  u32_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i32_t;\n", &err);
        } else if (short_bytes == 4) {
            WRITE_STR(f_types, "typedef unsigned short u32_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i32_t;\n", &err);
        } else if (int_bytes == 4) {
            WRITE_STR(f_types, "typedef unsigned int   u32_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i32_t;\n", &err);
        } else if (long_bytes == 4) {
            WRITE_STR(f_types, "typedef unsigned long  u32_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i32_t;\n", &err);
        }

        /* u64_t i64_t */
        if (char_bytes == 8) {
            WRITE_STR(f_types, "typedef unsigned char  u64_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i64_t;\n", &err);
        } else if (short_bytes == 8) {
            WRITE_STR(f_types, "typedef unsigned short u64_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i64_t;\n", &err);
        } else if (int_bytes == 8) {
            WRITE_STR(f_types, "typedef unsigned int   u64_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i64_t;\n", &err);
        } else if (long_bytes == 8) {
            WRITE_STR(f_types, "typedef unsigned long  u64_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i64_t;\n", &err);
        }

        /* u128_t i128_t */
        if (char_bytes == 16) {
            WRITE_STR(f_types, "typedef unsigned char  u128_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed char  i128_t;\n", &err);
        } else if (short_bytes == 16) {
            WRITE_STR(f_types, "typedef unsigned short u128_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed short i128_t;\n", &err);
        } else if (int_bytes == 16) {
            WRITE_STR(f_types, "typedef unsigned int   u128_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed int   i128_t;\n", &err);
        } else if (long_bytes == 16) {
            WRITE_STR(f_types, "typedef unsigned long  u128_t;\n", &err);
            WRITE_STR(f_types, "typedef   signed long  i128_t;\n", &err);
        }

        WRITE_CHR(f_types, '\n', &err);

        /* f8_t */
        if (float_bytes == 1) {
            WRITE_STR(f_types, "typedef float  f8_t;\n", &err);
        } else if (double_bytes == 1) {
            WRITE_STR(f_types, "typedef double f8_t;\n", &err);
        } else if (long_double_bytes == 1) {
            WRITE_STR(f_types, "typedef long double f8_t;\n", &err);
        }

        /* f16_t */
        if (float_bytes == 2) {
            WRITE_STR(f_types, "typedef float  f16_t;\n", &err);
        } else if (double_bytes == 2) {
            WRITE_STR(f_types, "typedef double f16_t;\n", &err);
        } else if (long_double_bytes == 2) {
            WRITE_STR(f_types, "typedef long double f16_t;\n", &err);
        }

        /* f32_t */
        if (float_bytes == 4) {
            WRITE_STR(f_types, "typedef float  f32_t;\n", &err);
        } else if (double_bytes == 4) {
            WRITE_STR(f_types, "typedef double f32_t;\n", &err);
        } else if (long_double_bytes == 4) {
            WRITE_STR(f_types, "typedef long double f32_t;\n", &err);
        }

        /* f64_t */
        if (float_bytes == 8) {
            WRITE_STR(f_types, "typedef float  f64_t;\n", &err);
        } else if (double_bytes == 8) {
            WRITE_STR(f_types, "typedef double f64_t;\n", &err);
        } else if (long_double_bytes == 8) {
            WRITE_STR(f_types, "typedef long double f64_t;\n", &err);
        }

        /* f128_t */
        if (float_bytes == 16) {
            WRITE_STR(f_types, "typedef float  f128_t;\n", &err);
        } else if (double_bytes == 16) {
            WRITE_STR(f_types, "typedef double f128_t;\n", &err);
        } else if (long_double_bytes == 16) {
            WRITE_STR(f_types, "typedef long double f128_t;\n", &err);
        }

        WRITE_CHR(f_types, '\n', &err);

        /* usize isize */
        if (ptr_bytes == 1) {
            WRITE_STR(f_types, "typedef u8_t usize_t;\n", &err);
            WRITE_STR(f_types, "typedef i8_t isize_t;\n", &err);
        } else if (ptr_bytes == 2) {
            WRITE_STR(f_types, "typedef u16_t usize_t;\n", &err);
            WRITE_STR(f_types, "typedef i16_t isize_t;\n", &err);
        } else if (ptr_bytes == 4) {
            WRITE_STR(f_types, "typedef u32_t usize_t;\n", &err);
            WRITE_STR(f_types, "typedef i32_t isize_t;\n", &err);
        } else if (ptr_bytes == 8) {
            WRITE_STR(f_types, "typedef u64_t usize_t;\n", &err);
            WRITE_STR(f_types, "typedef i64_t isize_t;\n", &err);
        } else if (ptr_bytes == 16) {
            WRITE_STR(f_types, "typedef u128_t usize_t;\n", &err);
            WRITE_STR(f_types, "typedef i128_t isize_t;\n", &err);
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
