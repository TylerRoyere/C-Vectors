#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vectors.h"

size_t
int_sqrt(size_t x)
{
    size_t ii;
    for (ii = 0; ii * ii < x; ii++);
    return ii;
}

int
main(int argc, char* argv[])
{
    size_t size, sqrt_size, temp, count;

    if (argc != 2) {
        printf("Usage: %s [max_num]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    size = (size_t)atoi(argv[1]) + 1;
    if (size <= 0) {
        printf("Invalid argument %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    sqrt_size = int_sqrt(size);


    vec_of(size_t) vv = init_vec(vv, 0);
    for (size_t ii = 0; ii < size; ii++) {
        vec_push(vv, 1);
    }
    vec_set(vv, 0, 0);
    vec_set(vv, 1, 0);

    for (size_t ii = 2; ii < sqrt_size; ii++)
        for (size_t jj = ii * ii; jj < size; jj += ii)
            vec_set(vv, (int)jj, 0);

    count = 0;
    vec_foreach_copy(vv, temp) {
        if (temp) count++;
    }

    destroy_vec(vv);

    printf("%zu primes below %zu\n", count, size-1);

    return 0;
}
