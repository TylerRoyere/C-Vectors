#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

#include "vector.h"

#define GENERATE_VECTOR_STRUCTURE(name) \
    typedef struct { struct vector* vec; } name

#ifdef VECTOR_HELPERS_INCLUDE_IMPL

#define NULLABLE_ASSIGNMENT(type, ptr) \
    NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, __COUNTER__)

#define NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, counter) \
    NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, anonymous_buff ## counter)

#define NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, buff_name) \
    type buff_name; \
    if ((ptr) == NULL) ptr = &buff_name; \
    *ptr 

#define GENERATE_VECTOR_STATIC_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_##copyable(name, type)

#define GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_true(name, type) \
    GENERATE_VECTOR_FUNCTIONS_COPYABLE_TRUE_PREFIX(static inline, name, type)

#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_TRUE_PREFIX(prefix, name, type) \
prefix name create_ ## name(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector(capacity, sizeof( type )), \
    }; \
} \
prefix name create_ ## name ##_cleared(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector_cleared(capacity, sizeof( type )), \
    }; \
} \
prefix void name##_fill(name vv) \
{ \
    vector_fill(vv.vec); \
} \
prefix void name##_fill_value(name vv, type fill) \
{ \
    vector_fill_value(vv.vec, &fill); \
} \
prefix void destroy_ ## name (name vv) \
{ \
    destroy_vector(vv.vec); \
} \
prefix int name##_size(name vv) \
{ \
    return vector_size(vv.vec); \
} \
prefix void name##_resize(name vv, const int new_capacity) \
{ \
    vector_resize(vv.vec, new_capacity); \
} \
prefix type name##_get(const name vv, const int index, int* err) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, err) = vector_get(vv.vec, index, &ret); \
    return ret; \
} \
prefix int name##_set(name vv, const int index, type val) \
{ \
    return vector_set(vv.vec, index, &val); \
} \
prefix type* name##_get_ref(name vv, const int index, int* err) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, err) = vector_get_ref(vv.vec, index, (void**)&ret); \
    return ret; \
} \
prefix void name##_push(name vv, type value) \
{ \
    vector_push(vv.vec, (void*)&value); \
} \
prefix type name##_pop(const name vv) \
{ \
    type ret; \
    vector_pop(vv.vec, &ret); \
    return ret; \
} \
prefix type name##_last(name vv, int* err) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, err) = vector_get(vv.vec, vector_size(vv.vec)-1, (void*)&ret); \
    return ret; \
} \
prefix type name##_first(name vv, int* err) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, err) = vector_get(vv.vec, 0, (void*)&ret); \
    return ret; \
} \
prefix type* name##_data(name vv) \
{ \
    return (type*) vector_data(vv.vec); \
} \
prefix type* name##_begin(name vv) \
{ \
    return ((type*) vector_data(vv.vec)) + 0; \
} \
prefix type* name##_end(name vv) \
{ \
    return ((type*) vector_data(vv.vec)) + vector_size(vv.vec); \
} \



#define GENERATE_VECTOR_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_FUNCTIONS_COPYABLE_##copyable(name, type)


#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_true(name, type) \
    GENERATE_VECTOR_FUNCTIONS_COPYABLE_TRUE_PREFIX(, name, type)

#endif

#define GENERATE_VECTOR_FUNCTION_PROTOTYPES(name, type, copyable) \
     GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_##copyable (name, type)

#define GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_true(name, type) \
name create_ ## name (const int capacity); \
name create_ ## name ## _cleared(const int capacity); \
void name##_fill(name vv); \
void name##_fill_value(name vv, type fill); \
void destroy_ ## name (name vv); \
int name##_size(name vv); \
void name##_resize(name vv, const int new_capacity); \
type name##_get(const name vv, const int index, int* err); \
int name##_set(name vv, const int index, type val); \
type* name##_get_ref(name vv, const int index, int* err); \
void name##_push(name vv, type value); \
type name##_pop(const name vv); \
type name##_last(name vv, int* err); \
type name##_first(name vv, int* err); \
type* name##_data(name vv); \
type* name##_begin(name vv); \
type* name##_end(name vv) \



//#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_false(type)
//

#endif
