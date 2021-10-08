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

struct vector;

struct vector {
    int size;
    int member_size;
    int capacity;
    void *data;
};

static struct vector* create_vector(const int capacity, const int member_size);
static struct vector* create_vector_cleared(const int capacity, const int member_size);
static struct vector* vector_fill_value(struct vector* vv, void* fill);
static struct vector* vector_fill(struct vector* vv);
static int destroy_vector(struct vector* vv);

static int vector_size(struct vector* vv);
static struct vector* vector_resize(struct vector* vv, const int new_capacity);

static int vector_get(struct vector* vv, const int index, void* ret);
static int vector_set(struct vector* vv, const int index, const void* val);
static int vector_get_ref(struct vector* vv, const int index, void** ret);

static struct vector* vector_push(struct vector* vv, void* data);
static struct vector* vector_pop(struct vector* vv, void* ret);
static int vector_last(struct vector* vv, void** ret);

static void* vector_data(struct vector* vv);


#endif
