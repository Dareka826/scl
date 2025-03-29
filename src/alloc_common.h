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

#endif
