#ifndef VECTORS_H
#define VECTORS_H 

#include <stdint.h>
#include <stddef.h>

#include "helpers.h"

#include "short_string.h"

#define VEC_TYPE_uint64_t   u64v
#define VEC_TYPE_int64_t    i64v
#define VEC_TYPE_uint32_t   u32v
#define VEC_TYPE_int32_t    i32v
#define VEC_TYPE_void_ptr   strv
#define VEC_TYPE_char_ptr   ptrv
#define VEC_TYPE_short_string   short_stringv
#define VEC_TYPE_i32v i32vv

#define VEC_STRUCT_NAME(T) VEC_TYPE_##T
#define vec_of(T) VEC_STRUCT_NAME(T)
#define vec_of_ptr(T) vec_of(T##_ptr)
#define vec_of_struct(T) vec_of(struct_##T)
#define vec_of_struct_ptr(T) vec_of_ptr(struct_##T)

#define GENERATE_VECTOR_FOR_TYPE(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(type)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(type), type, copyable)

#define GENERATE_VECTOR_FOR_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(type##_ptr)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(type##_ptr), type*, copyable)

#define GENERATE_VECTOR_FOR_STRUCT_TYPE(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(struct_##type)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(struct_##type), struct type, copyable)

#define GENERATE_VECTOR_FOR_STRUCT_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(VEC_STRUCT_NAME(struct_##type##_ptr)); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(VEC_STRUCT_NAME(struct_##type##_ptr), struct type*, copyable)

GENERATE_VECTOR_FOR_TYPE(uint64_t, true)
GENERATE_VECTOR_FOR_TYPE(int64_t, true)
GENERATE_VECTOR_FOR_TYPE(uint32_t, true)
GENERATE_VECTOR_FOR_TYPE(int32_t, true)

GENERATE_VECTOR_FOR_TYPE_PTR(char, true)
GENERATE_VECTOR_FOR_TYPE_PTR(void, true)

GENERATE_VECTOR_FOR_TYPE(short_string, true)
GENERATE_VECTOR_FOR_TYPE(i32v, true)

#define VECTOR_GENERIC(pre, x, post) \
    x : pre##x##post \

#define TYPE_TO_VECTOR(T, vec, post) \
    T : create_##vec##post
       
#define VECTOR_GENERICS(a, b) \
    VECTOR_GENERIC(a, u64v, b), \
    VECTOR_GENERIC(a, i64v, b), \
    VECTOR_GENERIC(a, u32v, b), \
    VECTOR_GENERIC(a, i32v, b), \
    VECTOR_GENERIC(a, strv, b), \
    VECTOR_GENERIC(a, ptrv, b), \
    VECTOR_GENERIC(a, short_stringv, b), \
    VECTOR_GENERIC(a, i32vv, b)

#define TYPE_TO_VECTORS(post) \
    TYPE_TO_VECTOR(uint64_t, u64v, post), \
    TYPE_TO_VECTOR(int64_t, i64v, post), \
    TYPE_TO_VECTOR(uint32_t, u32v, post), \
    TYPE_TO_VECTOR(int32_t, i32v, post), \
    TYPE_TO_VECTOR(char*, strv, post), \
    TYPE_TO_VECTOR(void*, ptrv, post), \
    TYPE_TO_VECTOR(short_string*, short_stringv, post), \
    TYPE_TO_VECTOR(i32v, i32vv, post)

#define create_vec(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS() \
    ) (size)

#define create_vec_cleared(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS(_cleared) \
    ) (size)

#define init_vec(vec, size) _Generic((vec), \
    VECTOR_GENERICS(create_,) \
    ) (size)

#define init_vec_cleared(vec, size) _Generic((vec), \
    VECTOR_GENERICS(create_,_cleared) \
    ) (size)

#define destroy_vec(a) _Generic((a), \
    VECTOR_GENERICS(destroy_,) \
    ) (a)

#define vec_fill_value(a, b) _Generic((a), \
    VECTOR_GENERICS(,_fill_value) \
    ) (a, b)

#define vec_fill(a) _Generic((a), \
    VECTOR_GENERICS(,_fill) \
    ) (a)

#define vec_size(a) _Generic((a), \
    VECTOR_GENERICS(,_size) \
    ) (a)

#define vec_resize(a, b) _Generic((a), \
    VECTOR_GENERICS(,_resize) \
    ) (a, b)

#define vec_set(a, b, c) _Generic((a), \
    VECTOR_GENERICS(,_set) \
    ) (a, b, c)

#define vec_get(a, b, c) _Generic((a), \
    VECTOR_GENERICS(,_get) \
    ) (a, b, c)

#define vec_get_ref(a, b, c) _Generic((a), \
    VECTOR_GENERICS(,_get_ref) \
    ) (a, b, c)

#define vec_push(a, b) _Generic((a), \
    VECTOR_GENERICS(,_push) \
    ) (a, b)

#define vec_pop(a, b) _Generic((a), \
    VECTOR_GENERICS(,_pop) \
    ) (a, b)

#define vec_last(a, b) _Generic((a), \
    VECTOR_GENERICS(,_last) \
    ) (a, b)

#define vec_data(a) _Generic((a), \
    VECTOR_GENERICS(,_data) \
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

#define vec_foreach_pop(a, b) \
        while (vec_size(a) && vec_pop(a, &b).vec)

/*
GENERATE_VECTOR_FUNCTION_PROTOTYPES(u64v, uint64_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(i64v, int64_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(u32v, uint32_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(i32v, int32_t, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(stringv, char*, true);
GENERATE_VECTOR_FUNCTION_PROTOTYPES(genericv, void*, true);
*/

#undef GENERATE_VECTOR_STRUCTURE
#undef GENERATE_VECTOR_FUNCTION_PROTOTYPES
#undef GENERATE_VECTOR_FOR_TYPE
#undef GENERATE_VECTOR_FOR_TYPE_PTR

#include "vector.c"

#endif
