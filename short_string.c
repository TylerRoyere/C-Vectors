#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "short_string.h"

void
short_string_print(struct short_string* ss)
{
    printf(SHORT_STRING_FORMAT"\n", ss->str);
}

struct short_string*
short_string_create(const char* str)
{
    struct short_string* ret = malloc(sizeof(struct short_string));
    assert(ret != NULL);

    strncpy(ret->str, str, SHORT_STRING_SIZE);
    return ret;
}
