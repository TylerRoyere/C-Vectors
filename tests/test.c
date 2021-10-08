#include <stdio.h>
#include <stdint.h>
#include "vectors.h"
#include "short_string.h"

int
test_short_string(void)
{
    short_string ss = short_string_create("Hello World!");
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
        ss = vec_get(ssv, ii);
        printf(SHORT_STRING_FORMAT"\n", ss.str);
    }

    destroy_vec(ssv);

    vec_of(vec_of(int32_t)) ivv = init_vec(ivv, 0);
    for (int ii = 0; ii < 4; ii++) {
        vec_push(ivv, vec_fill_value(create_vec(int32_t, 0), ii));
    }

    vec_of(int32_t) temp;
    vec_foreach_copy(ivv, temp) {
        printf("%d\n", vec_get(temp, 0));
    }

    vec_foreach_pop(ivv, temp) {
        printf("%d\n", vec_get(temp, 0));
        destroy_vec(temp);
    }
    destroy_vec(ivv);
}

int
test_declaration(void)
{
    vec_of(char) cv;
    vec_of(unsigned char) ucv;
    vec_of(short) sv;
    vec_of(unsigned short) usv;
    vec_of(int) iv;
    vec_of(unsigned int) uiv;
    vec_of(long) lv;
    vec_of(unsigned long) ulv;
    vec_of(long long) llv;
    vec_of(unsigned long long) ullv;
    vec_of(size_t) zv;
    vec_of(ssize_t) szv;

    vec_of(unsigned long long) voull;
    vec_of(char**) void_ptrv;
}

int
main(void)
{
    int good;
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
    vec_get(uv, 9);
    vec_get_check(uv, 9, &good);
    vec_get_ref(uv, 9);
    vec_get_ref_check(uv, 9, &good);
    vec_push(uv, 12);
    vec_pop(uv, NULL);
    vec_last(uv, NULL);
    vec_data(uv);
    destroy_vec(uv);

    vec_of(int) ivec;

    vec_of(void*) ptr_vec;
    vec_of(char*) str_vec;

    vec_of(int64_t) i64_vec;
    vec_of(uint64_t) u64_vec;
    vec_of(int32_t) i32_vec;
    vec_of(uint32_t) u32_vec;

    unsigned int temp2;

    test_short_string();
    return 0;
}
