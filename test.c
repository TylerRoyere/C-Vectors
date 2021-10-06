#include <stdio.h>
#include <stdint.h>
#include "vectors.h"

int
main(void)
{
    struct u64_vector uv;
    uint64_t* val;
    uv = create_vec(uint64_t, 0);
    destroy_vec(uv);
    uv = init_vec(uv, 0);
    destroy_vec(uv);
    uv = create_vec_cleared(uint64_t, 4);
    destroy_vec(uv);
    uv = init_vec_cleared(uv, 4);
    vec_fill_value(uv, 1);
    vec_fill(uv);
    vec_size(uv);
    vec_resize(uv, 16);
    vec_fill(uv);
    vec_set(uv, 9, 10);
    vec_get(uv, 9, NULL);
    vec_get_ref(uv, 9, NULL);
    vec_push(uv, 12);
    vec_pop(uv, NULL);
    vec_last(uv, NULL);
    vec_data(uv);

    return 0;
}
