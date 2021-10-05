#ifndef VECTORS_H
#define VECTORS_H 

#include <stdint.h>

#include "helpers.h"

#define VECTOR_GENERIC(op, x) \
    struct x : x##op \

#define VECTOR_GENERICS(op) \
        VECTOR_GENERIC(op, u64_vector), \
        VECTOR_GENERIC(op, i64_vector), \
        VECTOR_GENERIC(op, u32_vector), \
        VECTOR_GENERIC(op, i32_vector) \

#define vec_fill_value(a, b) _Generic((a), \
        VECTOR_GENERICS(_fill_value) \
        ) (a, b)

#define vec_fill(a) _Generic((a), \
        VECTOR_GENERICS(_fill) \
        ) (a)

#define vec_size(a) _Generic((a), \
        VECTOR_GENERICS(_size) \
        ) (a)

#define vec_resize(a, b) _Generic((a), \
        VECTOR_GENERICS(_resize) \
        ) (a, b)

#define vec_set(a, b, c) _Generic((a), \
        VECTOR_GENERICS(_set) \
        ) (a, b, c)

#define vec_get(a, b, c) _Generic((a), \
        VECTOR_GENERICS(_get) \
        ) (a, b, c)

#define vec_get_ref(a, b, c) _Generic((a), \
        VECTOR_GENERICS(_get_ref) \
        ) (a, b, c)

#define vec_push(a, b) _Generic((a), \
        VECTOR_GENERICS(_push) \
        ) (a, b)

#define vec_pop(a, b) _Generic((a), \
        VECTOR_GENERICS(_pop) \
        ) (a, b)

#define vec_last(a, b) _Generic((a), \
        VECTOR_GENERICS(_last) \
        ) (a, b)

#define vec_data(a) _Generic((a), \
        VECTOR_GENERICS(_data) \
        ) (a)

#define vec_foreach_copy_anonymous(a, b, counter) \
    const int length__##counter = vec_size(a); \
    int go_once__##counter = 1; \
    for (int foreach_loop_counter__##counter = 0; \
            foreach_loop_counter__##counter < length__##counter; \
            go_once__##counter = ++foreach_loop_counter__##counter )\
        for ((b = vec_get(a, foreach_loop_counter__##counter, NULL)); \
                go_once__##counter; \
                go_once__##counter=0) \

#define vec_foreach_copy_anonymous_indir(a, b, counter) \
    vec_foreach_copy_anonymous(a, b, counter)

#define vec_foreach_copy(a, b) \
    vec_foreach_copy_anonymous_indir(a, b, __COUNTER__)


GENERATE_VECTOR_STRUCTURE(u64_vector);
GENERATE_VECTOR_STRUCTURE(i64_vector);
GENERATE_VECTOR_STRUCTURE(u32_vector);
GENERATE_VECTOR_STRUCTURE(i32_vector);
GENERATE_VECTOR_STRUCTURE(string_vector);
GENERATE_VECTOR_STRUCTURE(generic_vector);

GENERATE_VECTOR_STATIC_FUNCTIONS(u64_vector, uint64_t, true)
GENERATE_VECTOR_STATIC_FUNCTIONS(i64_vector, int64_t, true)
GENERATE_VECTOR_STATIC_FUNCTIONS(u32_vector, uint32_t, true)
GENERATE_VECTOR_STATIC_FUNCTIONS(i32_vector, int32_t, true)
GENERATE_VECTOR_STATIC_FUNCTIONS(string_vector, char*, true)
GENERATE_VECTOR_STATIC_FUNCTIONS(generic_vector, void*, true)

/*
GENERATE_VECTOR_FUNCTION_PROTOTYPES(u64_vector, uint64_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(i64_vector, int64_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(u32_vector, uint32_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(i32_vector, int32_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(string_vector, char*, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(generic_vector, void*, true);
*/

#undef GENERATE_VECTOR_STRUCTURE
#undef GENERATE_VECTOR_FUNCTION_PROTOTYPES

#endif
