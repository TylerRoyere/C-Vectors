#ifndef VECTORS_H
#define VECTORS_H 

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#include "helpers.h"

#include "short_string.h"

/* Need to typedef standard types to names with no spaces */

typedef long long llong;
typedef unsigned long long ullong;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char uchar;

/* Mapping of standard types to fixed width versions */

#if SIZE_MAX == 0xFFFFFFFFFFFFFFFF
#define VEC_TYPE_size_t u64v
#define VEC_TYPE_ssize_t i64v
#elif SIZE_MAX == 0xFFFFFFFF
#define VEC_TYPE_size_t u32v
#define VEC_TYPE_ssize_t i32v
#elif SIZE_MAX == 0xFFFF
#define VEC_TYPE_size_t u32v
#define VEC_TYPE_ssize_t i32v
#else
#warning "No mapping for long long to fixed width integer"
#endif

#if ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
#define VEC_TYPE_ullong u64v
#define VEC_TYPE_llong i64v
#else 
#warning "No mapping for long long to fixed width integer"
#endif

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFF
#define VEC_TYPE_ulong u64v
#define VEC_TYPE_long i64v
#elif ULONG_MAX == 0xFFFFFFFF
#define VEC_TYPE_ulong u32v
#define VEC_TYPE_ulong i32v
#else 
#warning "No mapping for long to fixed width integer"
#endif

#if UINT_MAX == 0xFFFFFFFF
#define VEC_TYPE_uint u32v
#define VEC_TYPE_int i32v
#elif UINT_MAX == 0xFFFF
#define VEC_TYPE_uint u16v
#define VEC_TYPE_int i16v
#else 
#warning "No mapping for int to fixed width integer"
#endif

#if USHRT_MAX == 0xFFFF
#define VEC_TYPE_ushort u16v
#define VEC_TYPE_short i16v
#else
#warning "No mapping for short to fixed width integer"
#endif

#if UCHAR_MAX == 0xFF
#define VEC_TYPE_uchar u8v
#define VEC_TYPE_char i8v
#else
#warning "No mapping for char to fixed width integer"
#endif

/* Mandatory type to vector mappings */

#define VEC_TYPE_uint64_t       u64v
#define VEC_TYPE_int64_t        i64v
#define VEC_TYPE_uint32_t       u32v
#define VEC_TYPE_int32_t        i32v
#define VEC_TYPE_uint16_t       u16v
#define VEC_TYPE_int16_t        i16v
#define VEC_TYPE_uint8_t        u8v
#define VEC_TYPE_int8_t         i8v
#define VEC_TYPE_char_ptr       strv
#define VEC_TYPE_void_ptr       ptrv
#define VEC_TYPE_short_string   short_stringv
#define VEC_TYPE_i32v i32vv
#define VEC_TYPE_char_ptr_ptr char_ptr_ptrv

#define SPECIFIED_TYPE_TO_VECTOR(T) VEC_TYPE_##T
#define EXPAND_VECTOR_OF_CONCAT(a, T, b) a##T##b
#define vec_of(T) SPECIFIED_TYPE_TO_VECTOR(T)
#define ptr_to(T) EXPAND_VECTOR_OF_CONCAT(,T,_ptr)
#define struct(T) EXPAND_VECTOR_OF_CONCAT(struct_,T,)
#define unsigned(T) EXPAND_VECTOR_OF_CONCAT(u,T,)
#define long(T) EXPAND_VECTOR_OF_CONCAT(l,T,)

#define GENERATE_VECTOR_FOR_TYPE_INDIR(V, T, copyable) \
    GENERATE_VECTOR_STRUCTURE(V); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(V, T, copyable)

/* Gross hacks as an attempt to handle multi-keyword types */

#define GENERATE_VECTOR_FOR_TYPE(V, T, copyable) \
    GENERATE_VECTOR_FOR_TYPE_INDIR(vec_of(V), T, copyable)

#define GENERATE_VECTOR_FOR_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(vec_of(ptr_to(type))); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(vec_of(ptr_to(type)), type*, copyable)

#define GENERATE_VECTOR_FOR_STRUCT_TYPE(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(vec_of(struct(type))); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(vec_of(struct(type)), struct type, copyable)

#define GENERATE_VECTOR_FOR_STRUCT_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(vec_of(ptr_to(struct(type))));\
    GENERATE_VECTOR_STATIC_FUNCTIONS(vec_of(ptr_to(struct(type))), struct type*, copyable)

/* Generate vectors for int types */
GENERATE_VECTOR_FOR_TYPE(uint64_t, uint64_t, true)
GENERATE_VECTOR_FOR_TYPE(int64_t, int64_t, true)
GENERATE_VECTOR_FOR_TYPE(uint32_t, uint32_t, true)
GENERATE_VECTOR_FOR_TYPE(int32_t, int32_t, true)
GENERATE_VECTOR_FOR_TYPE(uint16_t, uint16_t, true)
GENERATE_VECTOR_FOR_TYPE(int16_t, int16_t, true)
GENERATE_VECTOR_FOR_TYPE(uint8_t, uint8_t, true)
GENERATE_VECTOR_FOR_TYPE(int8_t, int8_t, true)

/* Pointers are a bit tricky not sure I like this implementation */
GENERATE_VECTOR_FOR_TYPE(ptr_to(ptr_to(char)), char**, true)
GENERATE_VECTOR_FOR_TYPE(ptr_to(char), char*, true)
GENERATE_VECTOR_FOR_TYPE_PTR(void, true)

/* Generate vectors for other structures (including other vectors!) */
GENERATE_VECTOR_FOR_TYPE(short_string, short_string, true)
GENERATE_VECTOR_FOR_TYPE(i32v, i32v, true)

#define VECTOR_GENERIC(pre, x, post) \
    x : pre##x##post \

#define TYPE_TO_VECTOR(T, vec, post) \
    T : create_##vec##post
      
/* Association list from vector to operation */

#define VECTOR_GENERICS(a, b) \
    VECTOR_GENERIC(a, u64v, b), \
    VECTOR_GENERIC(a, i64v, b), \
    VECTOR_GENERIC(a, u32v, b), \
    VECTOR_GENERIC(a, i32v, b), \
    VECTOR_GENERIC(a, u16v, b), \
    VECTOR_GENERIC(a, i16v, b), \
    VECTOR_GENERIC(a, u8v, b), \
    VECTOR_GENERIC(a, i8v, b), \
    VECTOR_GENERIC(a, strv, b), \
    VECTOR_GENERIC(a, ptrv, b), \
    VECTOR_GENERIC(a, short_stringv, b), \
    VECTOR_GENERIC(a, i32vv, b)

/* Associate list from type to the vector that contains it */

#define TYPE_TO_VECTORS(post) \
    TYPE_TO_VECTOR(uint64_t, u64v, post), \
    TYPE_TO_VECTOR(int64_t, i64v, post), \
    TYPE_TO_VECTOR(uint32_t, u32v, post), \
    TYPE_TO_VECTOR(int32_t, i32v, post), \
    TYPE_TO_VECTOR(uint16_t, u16v, post), \
    TYPE_TO_VECTOR(int16_t, i16v, post), \
    TYPE_TO_VECTOR(uint8_t, u8v, post), \
    TYPE_TO_VECTOR(int8_t, i8v, post), \
    TYPE_TO_VECTOR(char*, strv, post), \
    TYPE_TO_VECTOR(void*, ptrv, post), \
    TYPE_TO_VECTOR(short_string*, short_stringv, post), \
    TYPE_TO_VECTOR(i32v, i32vv, post)

/* Generic macros (Where the fun begins) */

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

#define vec_get(a, b) _Generic((a), \
    VECTOR_GENERICS(,_get) \
    ) (a, b, NULL)

#define vec_get_check(a, b, c) _Generic((a), \
    VECTOR_GENERICS(,_get) \
    ) (a, b, c)

#define vec_get_ref(a, b) _Generic((a), \
    VECTOR_GENERICS(,_get_ref) \
    ) (a, b, NULL)

#define vec_get_ref_check(a, b, c) _Generic((a), \
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

/* Don't touch my stuff */

#define vec_foreach_copy_anonymous(a, b, counter) \
    const int length__##counter = vec_size(a); \
    int go_once__##counter = 1; \
    for (int foreach_loop_counter__##counter = 0; \
            foreach_loop_counter__##counter < length__##counter; \
            go_once__##counter = ++foreach_loop_counter__##counter )\
        for ((b = vec_get(a, foreach_loop_counter__##counter)); \
                go_once__##counter; \
                go_once__##counter=0) \

#define vec_foreach_copy_anonymous_indir(a, b, counter) \
    vec_foreach_copy_anonymous(a, b, counter)

/* Foreach macro for convenience */
#define vec_foreach_copy(V, value) \
    vec_foreach_copy_anonymous_indir(V, value, __COUNTER__)

/* Maybe you want to pop instead, that's fine too */
#define vec_foreach_pop(V, value) \
        while (vec_size(V) && vec_pop(V, &value).vec)

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
#undef GENERATE_VECTOR_FOR_STRUCT_TYPE
#undef GENERATE_VECTOR_FOR_STRUCT_TYPE_PTR

#include "vector.c"

#endif
