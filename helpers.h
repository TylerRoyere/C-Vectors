#ifndef HELPERS_H
#define HELPERS_H

#include <stddef.h>

#include "vector.h"

#define FLEX_ARRAY_VEC_SIZE(member_size, count) \
    (sizeof(struct vector) + (size_t)((size_t)(count) * (size_t)(member_size)))

#define NULLABLE_ASSIGNMENT(type, ptr) \
    NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, __COUNTER__)

#define NULLABLE_ASSIGNMENT_MAKE_NAME(type, ptr, counter) \
    NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, anonymous_buff ## counter)

#define NULLABLE_ASSIGNMENT_INTERNAL(type, ptr, buff_name) \
    type buff_name; \
    if ((ptr) == NULL) ptr = &buff_name; \
    *ptr 

#define GENERATE_VECTOR_STRUCTURE(name) \
    struct name { struct vector* vec; }


#define GENERATE_VECTOR_STATIC_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_##copyable(name, type)

#define GENERATE_VECTOR_STATIC_FUNCTIONS_COPYABLE_true(name, type) \
static inline struct name create_ ## name(const int capacity) \
{ \
    return (struct name ) { \
        .vec = create_vector(capacity, sizeof( type )), \
    }; \
} \
static inline struct name create_ ## name ##_cleared(const int capacity) \
{ \
    return (struct name ) { \
        .vec = create_vector_cleared(capacity, sizeof( type )), \
    }; \
} \
static inline void name##_fill(struct name vv) \
{ \
    vector_fill(vv.vec); \
} \
static inline void name##_fill_value(struct name vv, type fill) \
{ \
    vector_fill_value(vv.vec, &fill); \
} \
static inline int destroy_ ## name (struct name vv) \
{ \
    return destroy_vector(vv.vec); \
} \
static inline int name##_size(struct name vv) \
{ \
    return vector_size(vv.vec); \
} \
static inline struct name name##_resize(struct name vv, const int new_capacity) \
{ \
    return (struct name) { \
        .vec = vector_resize(vv.vec, new_capacity), \
    }; \
} \
static inline type name##_get(const struct name vv, const int index, int* good) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get(vv.vec, index, &ret); \
    return ret; \
} \
static inline int name##_set(struct name vv, const int index, type val) \
{ \
    return vector_set(vv.vec, index, &val); \
} \
static inline type* name##_get_ref(struct name vv, const int index, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, index, (void**)&ret); \
    return ret; \
} \
static inline struct name name##_push(struct name vv, type value) \
{ \
    return (struct name) { .vec = vector_push(vv.vec, (void*)&value), }; \
} \
static inline struct name name##_pop(const struct name vv, type* ret) \
{ \
    return (struct name) { .vec = vector_pop(vv.vec, ret), };  \
} \
static inline type* name##_last(struct name vv, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, vector_size(vv.vec)-1, (void**)&ret); \
    return ret; \
} \
static inline type* name##_data(struct name vv) \
{ \
    return (type*) vector_data(vv.vec); \
} \



#define GENERATE_VECTOR_FUNCTIONS(name, type, copyable) \
    GENERATE_VECTOR_FUNCTIONS_COPYABLE_##copyable(name, type)


#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_true(name, type) \
struct name create_ ## name(const int capacity) \
{ \
    return (struct name ) { \
        .vec = create_vector(capacity, sizeof( type )), \
    }; \
} \
struct name create_ ## name ##_cleared(const int capacity) \
{ \
    return (struct name ) { \
        .vec = create_vector_cleared(capacity, sizeof( type )), \
    }; \
} \
void name##_fill(struct name vv) \
{ \
    vector_fill(vv.vec); \
} \
void name##_fill_value(struct name vv, type fill) \
{ \
    vector_fill_value(vv.vec, &fill); \
} \
int destroy_ ## name (struct name vv) \
{ \
    return destroy_vector(vv.vec); \
} \
int name##_size(struct name vv) \
{ \
    return vector_size(vv.vec); \
} \
struct name name##_resize(struct name vv, const int new_capacity) \
{ \
    return (struct name) { \
        .vec = vector_resize(vv.vec, new_capacity), \
    }; \
} \
type name##_get(const struct name vv, const int index, int* good) \
{ \
    type ret; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get(vv.vec, index, &ret); \
    return ret; \
} \
int name##_set(struct name vv, const int index, type val) \
{ \
    return vector_set(vv.vec, index, &val); \
} \
type* name##_get_ref(struct name vv, const int index, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, index, (void**)&ret); \
    return ret; \
} \
struct name name##_push(struct name vv, type value) \
{ \
    return (struct name) { .vec = vector_push(vv.vec, (void*)&value), }; \
} \
struct name name##_pop(const struct name vv, type* ret) \
{ \
    return (struct name) { .vec = vector_pop(vv.vec, ret), };  \
} \
 type* name##_last(struct name vv, int* good) \
{ \
    type* ret = NULL; \
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, vector_size(vv.vec)-1, (void**)&ret); \
    return ret; \
} \
type* name##_data(struct name vv) \
{ \
    return (type*)vector_data(vv.vec); \
} \



#define GENERATE_VECTOR_FUNCTION_PROTOTYPES(name, type, copyable) \
     GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_##copyable (name, type)

#define GENERATE_VECTOR_FUNCTION_PROTOTYPES_COPYABLE_true(name, type) \
struct name create_ ## name (const int capacity); \
struct name create_ ## name ## _cleared(const int capacity); \
void name##_fill(struct name vv); \
void name##_fill_value(struct name vv, type fill); \
int destroy_ ## name (struct name vv); \
int name##_size(struct name vv); \
struct name name##_resize(struct name vv, const int new_capacity); \
type name##_get(const struct name vv, const int index, int* good); \
int name##_set(struct name vv, const int index, type val); \
type* name##_get_ref(struct name vv, const int index, int* good); \
struct name name##_push(struct name vv, type value); \
struct name name##_pop(const struct name vv, type* ret); \
type* name##_last(struct name vv, int* good); \
type* name##_data(struct name vv) \


//#define GENERATE_VECTOR_FUNCTIONS_COPYABLE_false(type)
//

#endif
