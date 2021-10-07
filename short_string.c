#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "short_string.h"

void
short_string_print(const short_string* ss)
{
    printf(SHORT_STRING_FORMAT, ss->str);
}

short_string
short_string_create(const char* str)
{
    short_string ret;

    strncpy(ret.str, str, SHORT_STRING_SIZE);
    return ret;
}
