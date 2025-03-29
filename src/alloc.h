#ifndef __SCL_ALLOC_H_WK7boqXA
#define __SCL_ALLOC_H_WK7boqXA

#include "types.h"
#include "macro.h"

enum {
    SCL_ALLOC_ERR_OK = 0,

    SCL_ALLOC_ERR_INVALID_ID           = 1 << 0,
    SCL_ALLOC_ERR_INVALID_ALLOC_STRUCT = 1 << 1
};


#define alloc_t(SIZE) SCL_CAT3(alloc, SIZE, _t)

#define alloc_init(SIZE) SCL_CAT3(alloc, SIZE, _init)
#define alloc_deinit(SIZE) SCL_CAT3(alloc, SIZE, _deinit)

#define alloc_new(SIZE) SCL_CAT3(alloc, SIZE, _new)
#define alloc_new_rand(SIZE) SCL_CAT3(alloc, SIZE, _new_rand)

#define alloc_free(SIZE) SCL_CAT3(alloc, SIZE, _free)
#define alloc_free_all(SIZE) SCL_CAT3(alloc, SIZE, _free_all)


#define SCL_ALLOC_DEFINE(SIZE) \
\
typedef struct SCL_CAT2(alloc, SIZE) { \
    bool_t valid; \
    ubyte *(ptrs[SIZE]); \
    usize    ids[SIZE]; \
} alloc_t(SIZE); \
\
void alloc_init(SIZE)(alloc_t(SIZE) * const in_ptr); \
void alloc_deinit(SIZE)(alloc_t(SIZE) * const in_ptr); \
\
ubyte *alloc_new(SIZE)(alloc_t(SIZE) * const in_ptr, usize in_id, size_t in_n); \
ubyte *alloc_new_rand(SIZE)(alloc_t(SIZE) * const in_ptr, usize * const out_id, size_t in_n); \
\
void alloc_free(SIZE)(alloc_t(SIZE) * const in_ptr, usize in_id); \
void alloc_free_all(SIZE)(alloc_t(SIZE) * const in_ptr);

#endif
