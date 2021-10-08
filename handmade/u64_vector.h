#ifndef U64_VECTOR_H
#define U64_VECTOR_H

#include <stdint.h>

#include "vector_helpers.h"

GENERATE_VECTOR_STRUCTURE(u64_vector);

GENERATE_VECTOR_FUNCTION_PROTOTYPES(u64_vector, uint64_t, true);
    //, uint64_t, true);

#endif
