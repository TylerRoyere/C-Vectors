#include <stdio.h>
#include <stdint.h>
#include "vectors.h"
#include "short_string.h"

int
test_short_string(void)
{
    short_string ss = short_string_create("Hello world!");
    printf("Text: "SHORT_STRING_FORMAT"\n", ss.str);
    printf("Text: ");
    short_string_print(&ss);
    printf("\n");

    vec_of(short_string) ssv = init_vec(ssv, 4);

    vec_push(ssv, short_string_create("1. First I pushed this onto the vector"));
    vec_push(ssv, short_string_create("2. Then I pushed this"));
    vec_push(ssv, short_string_create("3. Finally I added this sentence"));
    vec_push(ssv, short_string_create("4. This is awesome"));

    for (int ii = 0; ii < vec_size(ssv); ii++) {
        ss = vec_get(ssv, ii, NULL);
        printf(SHORT_STRING_FORMAT"\n", ss.str);
    }

    destroy_vec(ssv);
}

int
main(void)
{
    vec_of(uint64_t) uv;
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

    vec_of_ptr(void) ptr_vec;
    vec_of_ptr(char) str_vec;

    vec_of(int64_t) i64_vec;
    vec_of(uint64_t) u64_vec;
    vec_of(int32_t) i32_vec;
    vec_of(uint32_t) u32_vec;

    test_short_string();
    return 0;
}
