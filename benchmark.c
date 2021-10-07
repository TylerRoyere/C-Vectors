#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"

#define LOOPS 10000000

#define REPEATS 20

int
main(void)
{
    const int N = 0;
    for (int repetitions = 0; repetitions < REPEATS; repetitions++) {
        //struct i32_vector iv = create_i32_vector(N);
        //struct i32_vector iv2 = create_i32_vector(N);
        vec_of(int32_t) iv = init_vec(iv, N);
        struct i32_vector iv2 = create_vec(int32_t, N);

        for (int ii = 0; ii < LOOPS; ii++) {
            iv = vec_push(iv, ii);
        }

/*      
        int32_t temp;
        vec_foreach_copy(iv, temp) {
            iv2 = i32_vector_push(iv2, temp*2);
        }
*/

        int size = vec_size(iv);
        for (int ii = 0; ii < size; ii++) {
            iv2 = vec_push(iv2, vec_get(iv, ii, NULL));
        }

        struct i32_vector result = create_i32_vector_cleared(size + 1);

        for (int ii = 0; ii < size; ii++) {
            vec_data(iv)[ii] = vec_data(iv2)[ii] + vec_data(iv)[ii];
        }

        (void)vec_data(result)[LOOPS];
        destroy_vec(iv);
        destroy_vec(iv2);
        destroy_vec(result);
    /*    
    */
    }

    /*

    int32_t* a1 = malloc(LOOPS * sizeof(int32_t));
    int32_t* a2 = malloc(LOOPS * sizeof(int32_t));

    for (int ii = 0; ii < LOOPS; ii++) {
        a1[ii] = ii;
    }

    for (int ii = 0; ii < LOOPS; ii++) {
        a2[ii] = a1[ii] * 2;
    }

    for (int ii = 0; ii < LOOPS; ii++) {
        sum += a2[ii];
    }
    free(a1);
    free(a2);
    */

    return 0;
}
