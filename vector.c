#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "helpers.h"

#ifdef NDEBUG
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) 
#endif

inline struct vector*
create_vector(const int capacity, const int member_size)
{
    int alloc_capacity = capacity;
    if (alloc_capacity <= 0) alloc_capacity = DEFAULT_VECTOR_CAPACITY;
    
    struct vector* result = malloc(FLEX_ARRAY_VEC_SIZE(member_size, alloc_capacity));

    *result = (struct vector) {
        .capacity = alloc_capacity,
        .size = 0,
        .member_size = member_size,
    };

    ASSERT(result != NULL);

    return result;
}

inline struct vector*
create_vector_cleared(const int capacity, const int member_size)
{
    ASSERT(capacity > 0 && "Need positive, non-zero capacity");
    
    struct vector* result = calloc(
            FLEX_ARRAY_VEC_SIZE(member_size, capacity),
            sizeof(char));

    *result = (struct vector) {
        .capacity = capacity,
        .size = capacity,
        .member_size = member_size,
    };

    ASSERT(result != NULL);

    return result;
}

inline void
vector_fill_value(struct vector* vv, void* fill)
{
    if (fill != NULL) {
        for (int ii = 0; ii < vv->size; ii++) {
            memcpy(vv->data + (vv->member_size * ii), fill, (size_t)vv->member_size);
        }
    }
    vv->size = vv->capacity;
}

inline void
vector_fill(struct vector* vv)
{
    vv->size = vv->capacity;
}

inline int
destroy_vector(struct vector* vv)
{
    memset(vv, 0, FLEX_ARRAY_VEC_SIZE(vv->member_size, vv->capacity));
    free(vv);
    return 0;
}

inline int
vector_size(struct vector* vv)
{
    return vv->size;
}

inline struct vector*
vector_resize(struct vector* vv, const int new_capacity)
{
    ASSERT(new_capacity > 0);

    vv = realloc(vv, FLEX_ARRAY_VEC_SIZE(vv->member_size, new_capacity));

    ASSERT(vv != NULL);

    return vv;
}

inline int
vector_get(struct vector* vv, const int index, void* ret)
{
    void* ref = NULL;

    int result = vector_get_ref(vv, index, &ref);
    (void)result;
    ASSERT(result == 0);
    memcpy(ret, ref, (size_t)vv->member_size);

    return 0;
}

inline int
vector_set(struct vector* vv, const int index, const void* val)
{
    void* ref = NULL;

    int result = vector_get_ref(vv, index, &ref);
    (void)result;
    ASSERT(result == 0);
    memcpy(ref, val, (size_t)vv->member_size);

    return 0;
}

inline int
vector_get_ref(struct vector* vv, const int index, void** ret)
{
    if (index >= vv->size) return 1;
    
    *ret = vv->data + (index * vv->member_size);

    return 0;
}

inline struct vector*
vector_push(struct vector* vv, void* data)
{
    if (vv->size == vv->capacity) {
        vv = realloc(vv, FLEX_ARRAY_VEC_SIZE(vv->member_size, 2 * vv->capacity));
        ASSERT(vv != NULL);
        vv->capacity *= 2;
    }
    
    void* ref = vv->data + (vv->member_size * vv->size);
    memcpy(ref, data, (size_t)vv->member_size);
    vv->size++;

    return vv;
}

inline struct vector*
vector_pop(struct vector* vv, void* ret)
{
    vv->size--;
    if (ret != NULL) {
        void* ref = vv->data + (vv->member_size * vv->size);
        memcpy(ret, ref, (size_t)vv->member_size);
    }

    return vv;
}

inline int
vector_last(struct vector* vv, void** ret)
{
    return vector_get_ref(vv, vv->size-1, ret);
}

inline void*
vector_data(struct vector* vv)
{
    return (void*)vv->data;
}

#undef ASSERT
