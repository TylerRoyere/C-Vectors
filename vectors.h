#ifndef VECTORS_H
#define VECTORS_H 

#include <stdint.h>
#include <stddef.h>

#include "helpers.h"

#define VEC_TYPE_uint64_t   u64_vector
#define VEC_TYPE_int64_t    i64_vector
#define VEC_TYPE_uint32_t   u32_vector
#define VEC_TYPE_int32_t    i32_vector
#define VEC_TYPE_void_ptr   str_vector
#define VEC_TYPE_char_ptr   ptr_vector

#define VEC_STRUCT_NAME(T) VEC_TYPE_##T
#define vec_of(T) struct VEC_STRUCT_NAME(T)
#define vec_of_ptr(T) vec_of(T##_ptr)

#define GENERATE_VECTOR_FOR_TYPE(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(type)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(type), type, copyable)

#define GENERATE_VECTOR_FOR_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(type##_ptr)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(type##_ptr), type*, copyable)


GENERATE_VECTOR_FOR_TYPE(uint64_t, true)
GENERATE_VECTOR_FOR_TYPE(int64_t, true)
GENERATE_VECTOR_FOR_TYPE(uint32_t, true)
GENERATE_VECTOR_FOR_TYPE(int32_t, true)

GENERATE_VECTOR_FOR_TYPE_PTR(char, true)
GENERATE_VECTOR_FOR_TYPE_PTR(void, true)

#define VECTOR_GENERIC_ASSOC(pre, x, post) \
    struct x : pre##x##post \

#define VECTOR_GENERIC(op, vec) VECTOR_GENERIC_ASSOC(, vec, op)
#define VECTOR_MANAGER(op, vec, post) VECTOR_GENERIC_ASSOC(op, vec, post)

#define TYPE_TO_VECTOR(T, vec, post) \
    T : create_##vec##post
       
#define VECTOR_GENERICS(op) \
    VECTOR_GENERIC(op, u64_vector), \
    VECTOR_GENERIC(op, i64_vector), \
    VECTOR_GENERIC(op, u32_vector), \
    VECTOR_GENERIC(op, i32_vector), \
    VECTOR_GENERIC(op, str_vector), \
    VECTOR_GENERIC(op, ptr_vector)

#define VECTOR_MANAGERS(op, post) \
    VECTOR_MANAGER(op, u64_vector, post), \
    VECTOR_MANAGER(op, i64_vector, post), \
    VECTOR_MANAGER(op, u32_vector, post), \
    VECTOR_MANAGER(op, i32_vector, post), \
    VECTOR_MANAGER(op, str_vector, post), \
    VECTOR_MANAGER(op, ptr_vector, post)

#define TYPE_TO_VECTORS(post) \
    TYPE_TO_VECTOR(uint64_t, u64_vector, post), \
    TYPE_TO_VECTOR(int64_t, i64_vector, post), \
    TYPE_TO_VECTOR(uint32_t, u32_vector, post), \
    TYPE_TO_VECTOR(int32_t, i32_vector, post), \
    TYPE_TO_VECTOR(char*, str_vector, post), \
    TYPE_TO_VECTOR(void*, ptr_vector, post)

#define create_vec(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS() \
    ) (size)

#define create_vec_cleared(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS(_cleared) \
    ) (size)

#define init_vec(vec, size) _Generic((vec), \
    VECTOR_MANAGERS(create_,) \
    ) (size)

#define init_vec_cleared(vec, size) _Generic((vec), \
    VECTOR_MANAGERS(create_,_cleared) \
    ) (size)

#define destroy_vec(a) _Generic((a), \
    VECTOR_MANAGERS(destroy_,) \
    ) (a)

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
#undef GENERATE_VECTOR_FOR_TYPE
#undef GENERATE_VECTOR_FOR_TYPE_PTR

#include "vector.c"

#endif
