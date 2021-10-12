#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "vectors.h"
#include "short_string.h"

#define UNUSED __attribute__((unused))

int error_count;

#define ASSERT(x) if (!(x)) do { \
    fprintf(stderr, "%s:%d: **ASSERT FAILED** \""#x"\" False %s\n", __FILE__, __LINE__, __func__); \
    error_count++; \
    } while(0)


int
test_short_string(void)
{
    vec_of(short_string) ssv = init_vec(ssv, 4);

    const char* strs[] = {
        "1. First I pushed this onto the vector",
        "2. Then I pushed this",
        "3. Finally I added this sentenct",
        "4. This is awesome"
    };

    for (unsigned int ii = 0; ii < (sizeof(strs)/sizeof(*strs)); ii++) {
        vec_push(ssv, short_string_create(strs[ii]));
    }

    for (int ii = 0; ii < vec_size(ssv); ii++) {
        short_string ss = vec_get(ssv, ii);
        ASSERT(strcmp(ss.str, strs[ii]) == 0);
    }

    destroy_vec(ssv);

    vec_of(vec_of(int32_t)) ivv = init_vec(ivv, 0);
    int32_t expected[4];
    for (int ii = 0; ii < 4; ii++) {
        vec_push(ivv, vec_fill_value(create_vec(int32_t, 0), ii));
        expected[ii] = ii;
    }

    vec_of(int32_t) temp;
    int32_t* iter = expected;
    vec_foreach_copy(ivv, temp) {
        ASSERT( vec_get(temp, 0) == *(iter++));
    }
    
    iter = expected + 3;
    vec_foreach_pop(ivv, temp) {
        ASSERT( vec_get(temp, 0) == *(iter--));
        destroy_vec(temp);
    }
    destroy_vec(ivv);

    return 1;
}

void
test_declaration(void)
{
UNUSED    vec_of(char) cv;
UNUSED    vec_of(unsigned char) ucv;
UNUSED    vec_of(short) sv;
UNUSED    vec_of(unsigned short) usv;
UNUSED    vec_of(int) iv;
UNUSED    vec_of(unsigned int) uiv;
UNUSED    vec_of(long) lv;
UNUSED    vec_of(unsigned long) ulv;
UNUSED    vec_of(long long) llv;
UNUSED    vec_of(unsigned long long) ullv;
UNUSED    vec_of(size_t) zv;
UNUSED    vec_of(unsigned long long) voull;
UNUSED    vec_of(char**) void_ptrv;
}

void
test_cleared_initialization(void)
{
    int size = 20;
    vec_of(int) ivec = init_vec_cleared(ivec, size);

    for (int ii = 0; ii < size; ii++)  {
        ASSERT(vec_get(ivec, ii) == 0);
    }

    destroy_vec(ivec);

    ivec = create_vec_cleared(int, size);
    for (int ii = 0; ii < size; ii++) {
        ASSERT(vec_get(ivec, ii) == 0);
    }
    destroy_vec(ivec);
}

void
test_get(void)
{
    int size = 20;
    vec_of(int) ivec = init_vec(ivec, size);

    for (int ii = 0; ii < size; ii++) {
        vec_push(ivec, ii);
    }

    for (int ii = 0; ii < size; ii++) {
        ASSERT( vec_get(ivec, ii) == ii );
        ASSERT( *vec_get_ref(ivec, ii) == ii);
    }

    destroy_vec(ivec);
}

void
test_push_pop(void)
{
    int size = 20;
    vec_of(int) ivec = init_vec(ivec, 0);

    for (int ii = 0; ii < size; ii++) {
        vec_push(ivec, ii);
    }

    for (int ii = size-1; ii >= 0; ii--) {
        ASSERT( vec_pop(ivec) == ii );
    }

    destroy_vec(ivec);

}

void
test_set(void)
{
    int size = 20;
    vec_of(int) ivec = init_vec(ivec, size);

    vec_fill(ivec);

    for (int ii = 0; ii < size; ii++) {
        vec_set(ivec, ii, ii);
    }

    ASSERT( *vec_last(ivec) == size-1 );

    for (int ii = 0; ii < size; ii++) {
        ASSERT( vec_get(ivec, ii) == ii );
    }

    destroy_vec(ivec);
}

int
main(void)
{
    printf("\n\n");
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
    vec_pop(uv);
    vec_last(uv);
    vec_data(uv);
    destroy_vec(uv);

    test_cleared_initialization();
    test_get();

    test_short_string();
    if (error_count) printf("RECORDED ERRORS: %d\n", error_count);
    else printf("ALL TESTS PASSED\n");
    printf("\n");
    return error_count;
}
