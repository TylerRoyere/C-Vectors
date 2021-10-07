#ifndef SHORT_STRING_H
#define SHORT_STRING_H

#define SHORT_STRING_SIZE 128
#define SHORT_STRING_SIZE_TO_FORMAT_INDIR(x) #x 
#define SHORT_STRING_SIZE_TO_FORMAT(x) SHORT_STRING_SIZE_TO_FORMAT_INDIR(x)
#define SHORT_STRING_FORMAT "%."SHORT_STRING_SIZE_TO_FORMAT(SHORT_STRING_SIZE)"s"

struct short_string_ {
    char str[SHORT_STRING_SIZE];
};

typedef struct short_string_ short_string;

short_string short_string_create(const char* str);
void short_string_print(const short_string* ss);

#endif
