#ifndef VECTOR_C
#define VECTOR_C

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "vector_helpers.h"

#ifndef NDEBUG
#define ASSERT(x) assert(x)
#else
#define ASSERT(x) 
#endif

#define INLINE 

INLINE unsigned int
internal_ceil_log_2(unsigned int size)
{
    size--;
    if (size <= 0) return 0;
    for (unsigned int result = 0; ; size >>= 4) {
        if ((size >> 0) == 0) return result;
        if ((size >> 1) == 0) return result + 1;
        if ((size >> 2) == 0) return result + 2;
        if ((size >> 3) == 0) return result + 3;
        result += 4;
    }

    assert(0 && "Can't log size value");
    return 0;
}

INLINE unsigned int
pow_of_2(unsigned int power)
{
    return 1U << power;
}

inline struct vector*
create_vector(const unsigned int capacity, const unsigned int member_size)
{
    unsigned int alloc_capacity = capacity;
    if (alloc_capacity <= 0) alloc_capacity = DEFAULT_VECTOR_CAPACITY;
    
    struct vector* result = malloc(sizeof(struct vector));
    unsigned int log2_member_size = internal_ceil_log_2(member_size);
    void* data = malloc(alloc_capacity << log2_member_size);

    *result = (struct vector) {
        .capacity = alloc_capacity,
        .size = 0,
        .member_size = member_size,
        .member_size_log2 = log2_member_size,
        .data = data,
    };

    ASSERT(result != NULL);

    return result;
}

inline struct vector*
create_vector_cleared(const unsigned int capacity, const unsigned int member_size)
{
    ASSERT(capacity > 0 && "Need positive, non-zero capacity");
    
    struct vector* result = malloc(sizeof(struct vector));
    unsigned int log2_member_size = internal_ceil_log_2(member_size);
    void* data = calloc(capacity << log2_member_size, sizeof(char));

    *result = (struct vector) {
        .capacity = capacity,
        .size = capacity,
        .member_size = member_size,
        .member_size_log2 = log2_member_size,
        .data = data,
    };

    ASSERT(result != NULL);

    return result;
}

inline struct vector* 
vector_fill_value(struct vector* vv, void* fill)
{
    vv->size = vv->capacity;
    if (fill != NULL) {
        for (unsigned int ii = 0; ii < vv->capacity; ii++) {
            memcpy((char*)vv->data + (ii << vv->member_size_log2), fill,
                    vv->member_size);
        }
    }
    return vv;
}

inline struct vector* 
vector_fill(struct vector* vv)
{
    vv->size = vv->capacity;
    return vv;
}

inline int
destroy_vector(struct vector* vv)
{
    memset(vv->data, 0, vv->capacity << vv->member_size_log2);
    free(vv->data);
    memset(vv, 0, sizeof(*vv));
    free(vv);
    return 0;
}

inline unsigned int
vector_size(struct vector* vv)
{
    return vv->size;
}

inline struct vector*
vector_resize(struct vector* vv, const unsigned int new_capacity)
{
    ASSERT(new_capacity > 0);

    vv->data = realloc(vv->data, (new_capacity) << vv->member_size_log2);

    ASSERT(vv->data != NULL);

    vv->capacity = new_capacity;

    return vv;
}

inline int
vector_get(struct vector* vv, const unsigned int index, void* ret)
{
    void* ref = NULL;

    int result = vector_get_ref(vv, index, &ref);
    (void)result;
    ASSERT(result == 0);
    if (ref == NULL) {
        memset(ret, 0, pow_of_2(vv->member_size_log2));
        return 1;
    }
    memcpy(ret, ref, vv->member_size);

    return 0;
}

inline int
vector_set(struct vector* vv, const unsigned int index, const void* val)
{
    void* ref = NULL;

    int result = vector_get_ref(vv, index, &ref);
    (void)result;
    ASSERT(result == 0);
    if (ref == NULL) {
        return 1;
    }
    memcpy(ref, val, vv->member_size);

    return 0;
}

inline int
vector_get_ref(struct vector* vv, const unsigned int index, void** ret)
{
    if (index >= vv->size) return 1;
    
    *ret = (char*)vv->data + (index << vv->member_size_log2);

    return 0;
}

inline struct vector*
vector_push(struct vector* vv, void* data)
{
    if (vv->size == vv->capacity) {
        vv->data = realloc((char*)vv->data, 2 * vv->capacity << vv->member_size_log2);
        ASSERT(vv != NULL);
        vv->capacity *= 2;
    }
    
    void* ref = (char*)vv->data + (vv->size << vv->member_size_log2);
    memcpy(ref, data, vv->member_size);
    vv->size++;

    return vv;
}

inline struct vector*
vector_pop(struct vector* vv, void* ret)
{
    vv->size--;
    if (ret != NULL) {
        void* ref = (char*)vv->data + (vv->size << vv->member_size_log2);
        memcpy(ret, ref, vv->member_size);
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
#undef INLINE

#endif // VECTOR_C
