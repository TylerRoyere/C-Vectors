#ifndef VECTOR_H
#define VECTOR_H

/*
struct auto_vector {
    size_t length;
    size_t member_size;
    char* data;
};
*/

#define DEFAULT_VECTOR_CAPACITY (8)

#define INLINE

struct vector;

struct vector {
    unsigned int size;
    unsigned int member_size;
    unsigned int member_size_log2;
    unsigned int capacity;
    void *data;
};

INLINE struct vector* create_vector(const unsigned int capacity, const unsigned int member_size);
INLINE struct vector* create_vector_cleared(const unsigned int capacity, const unsigned int member_size);
INLINE struct vector* vector_fill_value(struct vector* vv, void* fill);
INLINE struct vector* vector_fill(struct vector* vv);
INLINE int destroy_vector(struct vector* vv);

INLINE unsigned int vector_size(struct vector* vv);
INLINE struct vector* vector_resize(struct vector* vv, const unsigned int new_capacity);

INLINE int vector_get(struct vector* vv, const unsigned int index, void* ret);
INLINE int vector_set(struct vector* vv, const unsigned int index, const void* val);
INLINE int vector_get_ref(struct vector* vv, const unsigned int index, void** ret);

INLINE struct vector* vector_push(struct vector* vv, void* data);
INLINE struct vector* vector_pop(struct vector* vv, void* ret);
INLINE int vector_last(struct vector* vv, void** ret);

INLINE void* vector_data(struct vector* vv);


#endif
