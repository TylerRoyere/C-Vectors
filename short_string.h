#ifndef SHORT_STRING_H
#define SHORT_STRING_H

#define SHORT_STRING_SIZE 128
#define STR_INDIR(x) #x 
#define STR(x) STR_INDIR(x)
#define SHORT_STRING_FORMAT "%."STR(SHORT_STRING_SIZE)"s"

struct short_string {
    char str[SHORT_STRING_SIZE];
};

struct short_string* short_string_create(const char* str);
void short_string_print(struct short_string* ss);

#endif
