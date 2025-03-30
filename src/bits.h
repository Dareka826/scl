#ifndef __SCL_BITS_H_YLRY182P
#define __SCL_BITS_H_YLRY182P

#include "types.h"

/* bit-fields can only be int or uint in C89
 * smallest int is at least 16 bits */

typedef struct bits8 {
    uint b0 : 1;
    uint b1 : 1;
    uint b2 : 1;
    uint b3 : 1;
    uint b4 : 1;
    uint b5 : 1;
    uint b6 : 1;
    uint b7 : 1;
} b8s_t;

typedef struct bits16 {
    uint b0  : 1;
    uint b1  : 1;
    uint b2  : 1;
    uint b3  : 1;
    uint b4  : 1;
    uint b5  : 1;
    uint b6  : 1;
    uint b7  : 1;
    uint b8  : 1;
    uint b9  : 1;
    uint b10 : 1;
    uint b11 : 1;
    uint b12 : 1;
    uint b13 : 1;
    uint b14 : 1;
    uint b15 : 1;
} b16s_t;

/* exact width types */

typedef struct u8x {
    uint val : 8;
} u8x;

typedef struct i8x {
    int val : 8;
} i8x;

typedef struct u16x {
    uint val : 16;
} u16x;

typedef struct i16x {
    int val : 16;
} i16x;

typedef struct u4x {
    uint val : 4;
} u4x;

typedef struct i4x {
    int val : 4;
} i4x;

#endif
