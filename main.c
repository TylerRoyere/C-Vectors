#include <stdio.h>

#include "vectors.h"
#include "short_string_vector.c"

typedef struct i32_vector i32vec;

int
main(int ac, char** av)
{
    i32vec iv = create_i32_vector(0);

    for (int ii = 0; ii < 10; ii++) {
        iv = vec_push(iv, ii);
    }

    for (int ii = 0; ii < i32_vector_size(iv); ii++) {
        printf("vector[%d] = %d\n", ii, i32_vector_get(iv, ii, NULL));
    }

    destroy_i32_vector(iv);

    struct u64_vector uv = create_u64_vector(0);
    for (unsigned int ii = 0; ii < 64; ii++) {
        uv = vec_push(uv, ii);
    }
    for (int ii = 0; ii < vec_size(uv); ii++) {
        printf("vector[%d] = %lu\n", ii, vec_get(uv, ii, NULL));
    }

    int32_t last = *vec_last(uv, NULL);

    uint64_t temp;
    vec_foreach_copy(uv, temp) {
        printf("%lu\n", temp);
    }

    uint64_t value;
    for (uv = u64_vector_pop(uv, &value); u64_vector_size(uv)+1; uv = u64_vector_pop(uv, &value)) {
        printf("%lu\n", value);
    }
    
    printf("Last = %d\n", last);

    destroy_u64_vector(uv);

    const char* strings[5] = {
        "1 Hello",
        "2 World",
        "3 This",
        "4 Is",
        "5 Awesome",
    };

    struct short_string_vector vv = create_short_string_vector(0);
    for (int ii = 0; ii < 5; ii++) {
        vv = short_string_vector_push(vv, short_string_create(strings[ii]));
    }

    for (int ii = 0; ii < short_string_vector_size(vv); ii++) {
        struct short_string temp;
        short_string_vector_get(vv, ii, &temp);
        short_string_print(&temp);
    }




    return 0;
}
