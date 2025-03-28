#include "alloc.h"
#include <stdlib.h>

#define SCL_ALLOC_IMPLEMENTATION(SIZE) \
\
void alloc_init(SIZE)(alloc_t(SIZE) * const in_ptr) { \
    size_t i; \
    \
    for (i = 0; i < SIZE; i += 1) { \
        in_ptr->ids[i] = 0; \
        in_ptr->ptrs[i] = 0; \
    } \
    \
    in_ptr->valid = 1; \
} \
\
void alloc_deinit(SIZE)(alloc_t(SIZE) * const in_ptr) { \
    alloc_free_all(SIZE)(in_ptr); \
    in_ptr->valid = 0; \
} \
\
ubyte *alloc_new(SIZE)(alloc_t(SIZE) * const in_ptr, usize in_id, size_t in_n) { \
    size_t i; \
    if (in_id == 0)         exit(SCL_ALLOC_ERR_INVALID_ID); \
    if (in_ptr->valid != 1) exit(SCL_ALLOC_ERR_INVALID_ALLOC_STRUCT); \
    \
    /* Check for duplicate ID */ \
    for (i = 0; i < SIZE; i += 1) \
        if (in_ptr->ids[i] == in_id) \
            return NULL; \
    \
    /* Find first free ID slot */ \
    for (i = 0; i < SIZE; i += 1) { \
        if (in_ptr->ids[i] == 0) { \
            in_ptr->ids[i] = in_id; \
            in_ptr->ptrs[i] = calloc(in_n, 1); \
            return in_ptr->ptrs[i]; \
        } \
    } \
    \
    /* No free slots */ \
    return NULL; \
} \
\
ubyte *alloc_new_rand(SIZE)(alloc_t(SIZE) * const in_ptr, usize * const out_id, size_t in_n) { \
    *out_id = rand() % RAND_MAX + 1; \
    return alloc_new(SIZE)(in_ptr, *out_id, in_n); \
} \
\
void alloc_free(SIZE)(alloc_t(SIZE) * const in_ptr, usize in_id) { \
    size_t i; \
    if (in_id == 0)         exit(SCL_ALLOC_ERR_INVALID_ID); \
    if (in_ptr->valid != 1) exit(SCL_ALLOC_ERR_INVALID_ALLOC_STRUCT); \
    \
    for (i = 0; i < SIZE; i += 1) { \
        if (in_ptr->ids[i] == in_id) { \
            in_ptr->ids[i] = 0; \
            \
            free(in_ptr->ptrs[i]); \
            in_ptr->ptrs[i] = NULL; \
            \
            break; \
        } \
    } \
} \
\
void alloc_free_all(SIZE)(alloc_t(SIZE) * const in_ptr) { \
    size_t i; \
    if (in_ptr->valid != 1) exit(SCL_ALLOC_ERR_INVALID_ALLOC_STRUCT); \
    \
    for (i = 0; i < SIZE; i += 1) { \
        if (in_ptr->ids[i] != 0) { \
            in_ptr->ids[i] = 0; \
            \
            free(in_ptr->ptrs[i]); \
            in_ptr->ptrs[i] = NULL; \
        } \
    } \
}
