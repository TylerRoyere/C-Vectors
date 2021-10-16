#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "vector_helpers.h"

void*
vector_internal_get_element_ref(const struct vector* vv, const int index)
{
    return &(((char*)(vv->data))[(index * vv->member_size)]);
}

void
vector_internal_resize(struct vector* vv, const int new_cap)
{
    vv->data = realloc(vv->data, (size_t)new_cap * (size_t)vv->member_size);
    assert(vv->data != NULL && "Vector: Allocation for data array failed!\n");
    vv->capacity = new_cap;
}

size_t
vector_internal_size_bytes(const struct vector* vv)
{
    return (size_t)vv->capacity * (size_t)vv->member_size;
}

struct vector*
create_vector(const int capacity, const int member_size)
{
    int alloc_capacity = capacity;
    if (alloc_capacity <= 0) alloc_capacity = DEFAULT_VECTOR_CAPACITY;
    
    struct vector* result = malloc(sizeof(struct vector));

    *result = (struct vector) {
        .capacity = alloc_capacity,
        .size = 0,
        .member_size = member_size,
        .data = NULL,
    };
    
    vector_internal_resize(result, alloc_capacity);

    return result;
}

struct vector*
create_vector_cleared(const int capacity, const int member_size)
{
    assert(capacity > 0 && "Need positive, non-zero capacity");
    
    struct vector* result = malloc(sizeof(struct vector));

    *result = (struct vector) {
        .capacity = capacity,
        .size = capacity,
        .member_size = member_size,
        .data = calloc((size_t)capacity, (size_t)member_size),
    };

    assert(result->data != NULL && "Vector: Cleared allocation for data array Failed\n");

    return result;
}

struct vector* 
vector_fill_value(struct vector* vv, void* fill)
{
    vv->size = vv->capacity;
    if (fill != NULL) {
        for (int ii = 0; ii < vv->capacity; ii++) {
            memcpy(vector_internal_get_element_ref(vv, ii), fill,
                    (size_t)vv->member_size);
        }
    }
    return vv;
}

struct vector* 
vector_fill(struct vector* vv)
{
    vv->size = vv->capacity;
    return vv;
}

int
destroy_vector(struct vector* vv)
{
    free(vv->data);
    free(vv);
    return 0;
}

int
vector_size(struct vector* vv)
{
    return vv->size;
}

struct vector*
vector_resize(struct vector* vv, const int new_capacity)
{
    assert(new_capacity > 0);

    vector_internal_resize(vv, new_capacity);

    return vv;
}

int
vector_get(struct vector* vv, const int index, void* ret)
{
    void* ref = NULL;

    int err = vector_get_ref(vv, index, &ref);
    if (!err)
        memcpy(ret, ref, (size_t)vv->member_size);
    else 
        memset(ret, 0, (size_t)vv->member_size);

    return err;
}

int
vector_set(struct vector* vv, const int index, const void* val)
{
    void* ref = NULL;

    int err = vector_get_ref(vv, index, &ref);
    if (!err)
        memcpy(ref, val, (size_t)vv->member_size);

    return err;
}

int
vector_get_ref(struct vector* vv, const int index, void** ret)
{
    if (index >= vv->size) return 1;
    
    *ret = vector_internal_get_element_ref(vv, index);

    return 0;
}

struct vector*
vector_push(struct vector* vv, void* data)
{
    if (vv->size == vv->capacity) {
        vector_internal_resize(vv, vv->capacity * 2);
    }
    
    void* ref = vector_internal_get_element_ref(vv, vv->size);
    memcpy(ref, data, (size_t)vv->member_size);
    vv->size++;

    return vv;
}

struct vector*
vector_pop(struct vector* vv, void* ret)
{
    vv->size--;
    if (ret != NULL) {
        void* ref = vector_internal_get_element_ref(vv, vv->size);
        memcpy(ret, ref, (size_t)vv->member_size);
    }

    return vv;
}

int
vector_last(struct vector* vv, void** ret)
{
    return vector_get_ref(vv, vv->size-1, ret);
}

void*
vector_data(struct vector* vv)
{
    return (void*)vv->data;
}

