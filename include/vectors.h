#ifndef VECTORS_H
#define VECTORS_H 

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#ifdef GENERATE_VECTOR_FUNCTIONS_INLINE
#define VECTOR_HELPERS_INCLUDE_IMPL
#endif
#include "vector_helpers.h"

#include "short_string.h"

/* Need to typedef standard types to names with no spaces */


#ifdef VEC_OF_WITHOUT_TYPEOF

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
#endif /* SIZE_MAX */

#if ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
#define VEC_TYPE_ullong u64v
#define VEC_TYPE_llong i64v
#else 
#warning "No mapping for long long to fixed width integer"
#endif /* ULLONG_MAX */

#if ULONG_MAX == 0xFFFFFFFFFFFFFFFF
#define VEC_TYPE_ulong u64v
#define VEC_TYPE_long i64v
#elif ULONG_MAX == 0xFFFFFFFF
#define VEC_TYPE_ulong u32v
#define VEC_TYPE_ulong i32v
#else 
#warning "No mapping for long to fixed width integer"
#endif /* ULONG_MAX */

#if UINT_MAX == 0xFFFFFFFF
#define VEC_TYPE_uint u32v
#define VEC_TYPE_int i32v
#elif UINT_MAX == 0xFFFF
#define VEC_TYPE_uint u16v
#define VEC_TYPE_int i16v
#else 
#warning "No mapping for int to fixed width integer"
#endif /* UINT_MAX */

#if USHRT_MAX == 0xFFFF
#define VEC_TYPE_ushort u16v
#define VEC_TYPE_short i16v
#else
#warning "No mapping for short to fixed width integer"
#endif /* USHRT_MAX */

#if UCHAR_MAX == 0xFF
#define VEC_TYPE_uchar u8v
#define VEC_TYPE_char i8v
#else
#warning "No mapping for char to fixed width integer"
#endif /* UCHAR_MAX */

#define vec_of(T) SPECIFIED_TYPE_TO_VECTOR(T)
#define ptr_to(T) EXPAND_VECTOR_OF_CONCAT(,T,_ptr)
#define struct(T) EXPAND_VECTOR_OF_CONCAT(struct_,T,)
#define unsigned(T) EXPAND_VECTOR_OF_CONCAT(u,T,)
#define long(T) EXPAND_VECTOR_OF_CONCAT(l,T,)
#define SPECIFIED_TYPE_TO_VECTOR(T) VEC_TYPE_##T
#define EXPAND_VECTOR_OF_CONCAT(a, T, b) a##T##b

/* Gross hacks as an attempt to handle multi-keyword types */
#define DECLARE_VECTOR_FOR_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(type); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(type, type*, copyable)

#define DECLARE_VECTOR_FOR_STRUCT_TYPE(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(type); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(type, struct type, copyable)

#define DECLARE_VECTOR_FOR_STRUCT_TYPE_PTR(type, copyable) \
    GENERATE_VECTOR_STRUCTURE(type);\
    GENERATE_VECTOR_STATIC_FUNCTIONS(type, struct type*, copyable)

#else

/* We can use typeof ! */
#define vec_of(T) __typeof__(create_vec(T,0))

#endif /* VEC_OF_WITHOUT_TYPEOF */


#ifndef GENERATE_VECTOR_FUNCTIONS_INLINE

#define DECLARE_VECTOR_FOR_TYPE_INDIR(V, T, copyable) \
    GENERATE_VECTOR_STRUCTURE(V); \
    GENERATE_VECTOR_FUNCTION_PROTOTYPES(V, T, copyable);

#define GENERATE_VECTOR_FUNCTION_DEFINITIONS(V, T, copyable) \
    GENERATE_VECTOR_FUNCTIONS(V, T, copyable)

#else

#define DECLARE_VECTOR_FOR_TYPE_INDIR(V, T, copyable) \
    GENERATE_VECTOR_STRUCTURE(V); \
    GENERATE_VECTOR_STATIC_FUNCTIONS(V, T, copyable)
#define GENERATE_VECTOR_FUNCTION_DEFINITIONS(V, T, copyable)

#endif /* GENERATE_VECTOR_FUNCTIONS_INLINE */

#define DECLARE_VECTOR_FOR_TYPE(V, T, copyable) \
    DECLARE_VECTOR_FOR_TYPE_INDIR(V, T, copyable)

#define VECTOR_GENERIC(pre, x, post) \
    x : pre##x##post \

#define TYPE_TO_VECTOR(T, vec, post) \
    T : create_##vec##post
      
/* Generic macros (Where the fun begins) */

#define create_vec(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS(), \
    default: (void) "Invalid type parameter, No vector exists for type" \
    ) (size)

#define create_vec_cleared(T, size) _Generic((*(T*)NULL), \
    TYPE_TO_VECTORS(_cleared), \
    default: (void) "Invalid type parameter, No vector exists for type" \
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

#define vec_pop(a) _Generic((a), \
    VECTOR_GENERICS(,_pop) \
    ) (a)

#define vec_first(a) _Generic((a), \
    VECTOR_GENERICS(,_first) \
    ) (a, NULL)

#define vec_first_check(a, b) _Generic((a), \
    VECTOR_GENERICS(,_first) \
    ) (a, b)

#define vec_last(a) _Generic((a), \
    VECTOR_GENERICS(,_last) \
    ) (a, NULL)

#define vec_last_check(a, b) _Generic((a), \
    VECTOR_GENERICS(,_last) \
    ) (a, b)

#define vec_data(a) _Generic((a), \
    VECTOR_GENERICS(,_data) \
    ) (a)

#define vec_begin(a) _Generic((a), \
    VECTOR_GENERICS(,_begin) \
    ) (a)

#define vec_end(a) _Generic((a), \
    VECTOR_GENERICS(,_end) \
    ) (a)

/* Don't touch my stuff */

#define ANONYMOUS_VEC_FOREACH_COPY(a, b, counter) \
    const int length__##counter = vec_size(a); \
    int go_once__##counter = 1; \
    for (int foreach_loop_counter__##counter = 0; \
            foreach_loop_counter__##counter < length__##counter; \
            go_once__##counter = ++foreach_loop_counter__##counter )\
        for ((b = vec_get(a, foreach_loop_counter__##counter)); \
                go_once__##counter; \
                go_once__##counter=0)

#define ANONYMOUS_VEC_FOREACH_POP(a, b, counter) \
    for (int go_once__##counter = 1; vec_size(a); go_once__##counter = 1) \
        for (b = vec_pop(a); go_once__##counter; go_once__##counter = 0)

/* Foreach macro for convenience */
#define vec_foreach_copy(V, value) \
    ANONYMOUS_VEC_FOREACH_COPY(V, value, __COUNTER__)

/* Maybe you want to pop instead, that's fine too */
#define vec_foreach_pop(V, value) \
    ANONYMOUS_VEC_FOREACH_POP(V, value, __COUNTER__)

#include "vector_autogen.h"

#undef GENERATE_VECTOR_STRUCTURE
#undef GENERATE_VECTOR_FUNCTION_PROTOTYPES
#undef DECLARE_VECTOR_FOR_TYPE
#undef DECLARE_VECTOR_FOR_TYPE_PTR
#undef DECLARE_VECTOR_FOR_STRUCT_TYPE
#undef DECLARE_VECTOR_FOR_STRUCT_TYPE_PTR
#undef GENERATE_VECTOR_STRUCTURE

#ifdef GENERATE_VECTOR_FUNCTIONS_INLINE
#undef NULLABLE_ASSIGNMENT
#undef NULLABLE_ASSIGNMENT_MAKE_NAME
#undef NULLABLE_ASSIGNMENT_INTERNAL
#undef GENERATE_VECTOR_STATIC_FUNCTIONS
#undef GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_true
#undef GENERATE_VECTOR_FUNCTIONS_COPYABLE_TRUE_PREFIX
#undef GENERATE_VECTOR_FUNCTIONS_COPYABLE_true
#endif

#undef VECTOR_HELPERS_INCLUDE_IMPL

//#include "vector.c"

#endif

