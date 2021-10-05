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
    char data[];
};

struct vector* create_vector(const int capacity, const int member_size);
struct vector* create_vector_cleared(const int capacity, const int member_size);
void vector_fill_value(struct vector* vv, void* fill);
void vector_fill(struct vector* vv);
int destroy_vector(struct vector* vv);

int vector_size(struct vector* vv);
struct vector* vector_resize(struct vector* vv, const int new_capacity);

int vector_get(struct vector* vv, const int index, void* ret);
int vector_set(struct vector* vv, const int index, const void* val);
int vector_get_ref(struct vector* vv, const int index, void** ret);

struct vector* vector_push(struct vector* vv, void* data);
struct vector* vector_pop(struct vector* vv, void* ret);
int vector_last(struct vector* vv, void** ret);

void* vector_data(struct vector* vv);


#endif
