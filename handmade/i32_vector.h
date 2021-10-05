#ifndef I32_VEC_H
#define I32_VEC_H

#include <stdint.h>

#include "vector.h"

struct i32_vector {
    struct vector* vec;
};

struct i32_vector create_i32_vector(const int capacity);
int destroy_i32_vector(struct i32_vector vv);

int i32_vector_size(struct i32_vector vv);
struct i32_vector i32_vector_resize(struct i32_vector vv, const int new_capacity);

int32_t i32_vector_get(const struct i32_vector vv, const int index, int* good);
int i32_vector_set(struct i32_vector vv, const int index, int32_t val);
int32_t* i32_vector_get_ref(const struct i32_vector vv, const int index, int* good);

struct i32_vector i32_vector_push(struct i32_vector vv, int32_t value);
struct i32_vector i32_vector_pop(const struct i32_vector vv, int32_t* ret);
int32_t* i32_vector_last(const struct i32_vector vv, int* good);


#endif
