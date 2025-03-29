#ifndef __SC_MACRO_H_YePLoI4I
#define __SC_MACRO_H_YePLoI4I

#define __SCL_STR_INTERNAL(x) #x
#define SC_STR(x) __SCL_STR_INTERNAL(x)

#define __SCL_CAT2_INTERNAL(a, b) a ## b
#define SCL_CAT2(a, b) __SCL_CAT2_INTERNAL(a, b)

#define __SCL_CAT3_INTERNAL(a, b, c) a ## b ## c
#define SCL_CAT3(a, b, c) __SCL_CAT3_INTERNAL(a, b, c)

#endif
