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

static inline int
internal_ceil_log_2(int size)
{
    size >>= 1;
    for (int result = 0; ; size >>= 4) {
        if ((size >> 0) == 0) return result;
        if ((size >> 1) == 0) return result + 1;
        if ((size >> 2) == 0) return result + 2;
        if ((size >> 3) == 0) return result + 3;
        result += 4;
    }

    assert(0 && "Can't log size value");
    return 0;
}

static inline int
pow_of_2(int power)
{
    return 1 << power;
}

inline struct vector*
create_vector(const int capacity, const int member_size)
{
    int alloc_capacity = capacity;
    if (alloc_capacity <= 0) alloc_capacity = DEFAULT_VECTOR_CAPACITY;
    
    struct vector* result = malloc(FLEX_ARRAY_VEC_SIZE(member_size, alloc_capacity));

    *result = (struct vector) {
        .capacity = alloc_capacity,
        .size = 0,
        .member_size = internal_ceil_log_2(member_size),
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
        .member_size = internal_ceil_log_2(member_size),
    };

    ASSERT(result != NULL);

    return result;
}

inline void
vector_fill_value(struct vector* vv, void* fill)
{
    if (fill != NULL) {
        for (int ii = 0; ii < vv->size; ii++) {
            memcpy(vv->data + (size_t)(ii << vv->member_size), fill,
                    (size_t)pow_of_2(vv->member_size));
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
    memset(vv, 0, FLEX_ARRAY_VEC_SIZE(pow_of_2(vv->member_size), vv->capacity));
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

    vv = realloc(vv, FLEX_ARRAY_VEC_SIZE(pow_of_2(vv->member_size), new_capacity));

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
    memcpy(ret, ref, (size_t)pow_of_2(vv->member_size));

    return 0;
}

inline int
vector_set(struct vector* vv, const int index, const void* val)
{
    void* ref = NULL;

    int result = vector_get_ref(vv, index, &ref);
    (void)result;
    ASSERT(result == 0);
    memcpy(ref, val, (size_t)pow_of_2(vv->member_size));

    return 0;
}

inline int
vector_get_ref(struct vector* vv, const int index, void** ret)
{
    if (index >= vv->size) return 1;
    
    *ret = vv->data + (index << vv->member_size);

    return 0;
}

inline struct vector*
vector_push(struct vector* vv, void* data)
{
    if (vv->size == vv->capacity) {
        vv = realloc(vv, FLEX_ARRAY_VEC_SIZE(pow_of_2(vv->member_size), 2 * vv->capacity));
        ASSERT(vv != NULL);
        vv->capacity *= 2;
    }
    
    void* ref = vv->data + (vv->size << vv->member_size);
    memcpy(ref, data, (size_t)pow_of_2(vv->member_size));
    vv->size++;

    return vv;
}

inline struct vector*
vector_pop(struct vector* vv, void* ret)
{
    vv->size--;
    if (ret != NULL) {
        void* ref = vv->data + (vv->size << vv->member_size);
        memcpy(ret, ref, (size_t)pow_of_2(vv->member_size));
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
