#include "short_string.h"

#include "vector.h"

struct short_string_vector {
    struct vector* vec;
};

struct short_string_vector
create_short_string_vector(const int capacity)
{
    return (struct short_string_vector) { 
        .vec = create_vector(capacity, sizeof(struct short_string)),
    };
}
int
destroy_short_string_vector(struct short_string_vector vv)
{
    return destroy_vector(vv.vec);
}
int
short_string_vector_size(struct short_string_vector vv)
{
    return vector_size(vv.vec);
}
struct short_string_vector
short_string_vector_resize(struct short_string_vector vv, const int new_capacity)
{
    return (struct short_string_vector) {
        .vec = vector_resize(vv.vec, new_capacity),
    };
}
int
short_string_vector_get(struct short_string_vector vv, const int index, struct short_string* ret)
{
    return vector_get(vv.vec, index, ret);
}
int
short_string_vector_set(struct short_string_vector vv, const int index, struct short_string* set)
{
    return vector_set(vv.vec, index, set);
}
int
short_string_vector_get_ref(struct short_string_vector vv, const int index, struct short_string** ref)
{
    return vector_get_ref(vv.vec, index, (void**)ref);
}
struct short_string_vector
short_string_vector_push(struct short_string_vector vv, struct short_string* value)
{
    return (struct short_string_vector) {
        .vec = vector_push(vv.vec, value),
    };
}
struct short_string_vector
short_string_vector_pop(struct short_string_vector vv, struct short_string* ret)
{
    return (struct short_string_vector) {
        .vec = vector_pop(vv.vec, ret),
    };
}
int
short_string_vector_last(struct short_string_vector vv, struct short_string** ret)
{
    return vector_last(vv.vec, (void**)ret);
}
