#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

#include "vector.h"

#define FLEX_ARRAY_VEC_SIZE(member_size, count) \
    (sizeof(struct vector) + (size_t)((count) << member_size))

#define NULLABLE_ASSIGNMENT(type, ptr) \
    NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, __COUNTER__)

#define NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, counter) \
    NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, anonymous_buff ## counter)

#define NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, buff_name) \
    type buff_name; \
    if ((ptr) == NULL) ptr = &buff_name; \
    *ptr 

#define GENERATE_VECTOR_STRUCTURE(name) \
    typedef struct { struct vector* vec; } name


#define GENERATE_VECTOR_STATIC_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_##copyable(name, type)

#define GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_true(name, type) \
static inline name create_ ## name(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector(capacity, sizeof( type )), \
    }; \
} \
static inline name create_ ## name ##_cleared(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector_cleared(capacity, sizeof( type )), \
    }; \
} \
static inline name name##_fill(name vv) \
{ \
    vector_fill(vv.vec); \
    return vv; \
} \
static inline name name##_fill_value(name vv, type fill) \
{ \
    vector_fill_value(vv.vec, &fill); \
    return vv; \
} \
static inline int destroy_ ## name (name vv) \
{ \
    return destroy_vector(vv.vec); \
} \
static inline int name##_size(name vv) \
{ \
    return vector_size(vv.vec); \
} \
static inline name name##_resize(name vv, const int new_capacity) \
{ \
    return (name) { \
        .vec = vector_resize(vv.vec, new_capacity), \
    }; \
} \
static inline type name##_get(const name vv, const int index, int* good) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get(vv.vec, index, &ret); \
    return ret; \
} \
static inline int name##_set(name vv, const int index, type val) \
{ \
    return vector_set(vv.vec, index, &val); \
} \
static inline type* name##_get_ref(name vv, const int index, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, index, (void**)&ret); \
    return ret; \
} \
static inline name name##_push(name vv, type value) \
{ \
    return (name) { .vec = vector_push(vv.vec, (void*)&value), }; \
} \
static inline name name##_pop(const name vv, type* ret) \
{ \
    return (name) { .vec = vector_pop(vv.vec, ret), };  \
} \
static inline type* name##_last(name vv, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, vector_size(vv.vec)-1, (void**)&ret); \
    return ret; \
} \
static inline type* name##_data(name vv) \
{ \
    return (type*) vector_data(vv.vec); \
} \



#define GENERATE_VECTOR_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_FUNCTIONS_COPYABLE_##copyable(name, type)


#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_true(name, type) \
name create_ ## name(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector(capacity, sizeof( type )), \
    }; \
} \
name create_ ## name ##_cleared(const int capacity) \
{ \
    return (name ) { \
        .vec = create_vector_cleared(capacity, sizeof( type )), \
    }; \
} \
name name##_fill(name vv) \
{ \
    vector_fill(vv.vec); \
    return vv; \
} \
name name##_fill_value(name vv, type fill) \
{ \
    vector_fill_value(vv.vec, &fill); \
    return vv; \
} \
int destroy_ ## name (name vv) \
{ \
    return destroy_vector(vv.vec); \
} \
int name##_size(name vv) \
{ \
    return vector_size(vv.vec); \
} \
name name##_resize(name vv, const int new_capacity) \
{ \
    return (name) { \
        .vec = vector_resize(vv.vec, new_capacity), \
    }; \
} \
type name##_get(const name vv, const int index, int* good) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get(vv.vec, index, &ret); \
    return ret; \
} \
int name##_set(name vv, const int index, type val) \
{ \
    return vector_set(vv.vec, index, &val); \
} \
type* name##_get_ref(name vv, const int index, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, index, (void**)&ret); \
    return ret; \
} \
name name##_push(name vv, type value) \
{ \
    return (name) { .vec = vector_push(vv.vec, (void*)&value), }; \
} \
name name##_pop(const name vv, type* ret) \
{ \
    return (name) { .vec = vector_pop(vv.vec, ret), };  \
} \
 type* name##_last(name vv, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, vector_size(vv.vec)-1, (void**)&ret); \
    return ret; \
} \
type* name##_data(name vv) \
{ \
    return (type*)vector_data(vv.vec); \
} \



#define GENERATE_VECTOR_FUNCTION_PROTOTYPES(name, type, copyable) \
     GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_##copyable (name, type)

#define GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_true(name, type) \
name create_ ## name (const int capacity); \
name create_ ## name ## _cleared(const int capacity); \
name name##_fill(name vv); \
name name##_fill_value(name vv, type fill); \
int destroy_ ## name (name vv); \
int name##_size(name vv); \
name name##_resize(name vv, const int new_capacity); \
type name##_get(const name vv, const int index, int* good); \
int name##_set(name vv, const int index, type val); \
type* name##_get_ref(name vv, const int index, int* good); \
name name##_push(name vv, type value); \
name name##_pop(const name vv, type* ret); \
type* name##_last(name vv, int* good); \
type* name##_data(name vv) \


//#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_false(type)
//

#endif
