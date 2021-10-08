#include <stddef.h>

#include "i32_vector.h"
#include "vector_helpers.h"

struct i32_vector
create_i32_vector(const int capacity)
{
    return (struct i32_vector) {
        .vec = create_vector(capacity, sizeof(int32_t)),
    };
}

int
destroy_i32_vector(struct i32_vector vv)
{
    return destroy_vector(vv.vec);
}

int
i32_vector_size(struct i32_vector vv)
{
    return vector_size(vv.vec);
}

struct i32_vector
i32_vector_resize(struct i32_vector vv, const int new_capacity)
{
    return (struct i32_vector) {
        .vec = vector_resize(vv.vec, new_capacity),
    };
}

int32_t
i32_vector_get(const struct i32_vector vv, const int index, int* good)
{
    int ret = 0;
    NULLABLE_ASSIGNMENT(int, good) = vector_get(vv.vec, index, &ret);
    return ret;
}

int
i32_vector_set(struct i32_vector vv, const int index, int32_t val)
{
    return vector_set(vv.vec, index, &val);
}

int32_t*
i32_vector_get_ref(const struct i32_vector vv, const int index, int* good)
{
    int32_t* ret = NULL;
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, index, (void**)&ret);
    return ret;
}

struct i32_vector
i32_vector_push(struct i32_vector vv, int32_t value)
{
    return (struct i32_vector) { .vec = vector_push(vv.vec, (void*)&value), };
}

struct i32_vector
i32_vector_pop(const struct i32_vector vv, int32_t* ret)
{
    return (struct i32_vector) { .vec = vector_pop(vv.vec, ret), };
}

int32_t*
i32_vector_last(const struct i32_vector vv, int* good)
{
    int32_t* ret = NULL;
    NULLABLE_ASSIGNMENT(int, good) = vector_get_ref(vv.vec, vector_size(vv.vec), (void**)&ret);
    return ret;
}
