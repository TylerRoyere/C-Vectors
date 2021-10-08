#ifndef VECTOR_AUTOGEN_H
#define VECTOR_AUTOGEN_H


/* Mappings from contained type to vector type */
#define VEC_TYPE_uint64_t u64v
#define VEC_TYPE_int64_t i64v
#define VEC_TYPE_uint32_t u32v
#define VEC_TYPE_int32_t i32v
#define VEC_TYPE_uint16_t u16v
#define VEC_TYPE_int16_t i16v
#define VEC_TYPE_uint8_t u8v
#define VEC_TYPE_int8_t i8v
#define VEC_TYPE_char_ptr strv
#define VEC_TYPE_void_ptr ptrv
#define VEC_TYPE_char_ptr_ptr char_ptr_ptrv
#define VEC_TYPE_short_string short_str_v
#define VEC_TYPE_i32v i32vv


/* Generate wrappers for vector of contained type */
GENERATE_VECTOR_FOR_TYPE(uint64_t, uint64_t, true)
GENERATE_VECTOR_FOR_TYPE(int64_t, int64_t, true)
GENERATE_VECTOR_FOR_TYPE(uint32_t, uint32_t, true)
GENERATE_VECTOR_FOR_TYPE(int32_t, int32_t, true)
GENERATE_VECTOR_FOR_TYPE(uint16_t, uint16_t, true)
GENERATE_VECTOR_FOR_TYPE(int16_t, int16_t, true)
GENERATE_VECTOR_FOR_TYPE(uint8_t, uint8_t, true)
GENERATE_VECTOR_FOR_TYPE(int8_t, int8_t, true)
GENERATE_VECTOR_FOR_TYPE(ptr_to(char), char*, true)
GENERATE_VECTOR_FOR_TYPE(ptr_to(void), void*, true)
GENERATE_VECTOR_FOR_TYPE(ptr_to(ptr_to(char)), char**, true)
GENERATE_VECTOR_FOR_TYPE(short_string, short_string, true)
GENERATE_VECTOR_FOR_TYPE(i32v, i32v, true)


/* Map vector types to that vectors implementation */
#define VECTOR_GENERICS(a, b) \
    VECTOR_GENERIC(a, u64v, b), \
    VECTOR_GENERIC(a, i64v, b), \
    VECTOR_GENERIC(a, u32v, b), \
    VECTOR_GENERIC(a, i32v, b), \
    VECTOR_GENERIC(a, u16v, b), \
    VECTOR_GENERIC(a, i16v, b), \
    VECTOR_GENERIC(a, u8v, b), \
    VECTOR_GENERIC(a, i8v, b), \
    VECTOR_GENERIC(a, strv, b), \
    VECTOR_GENERIC(a, ptrv, b), \
    VECTOR_GENERIC(a, char_ptr_ptrv, b), \
    VECTOR_GENERIC(a, short_str_v, b), \
    VECTOR_GENERIC(a, i32vv, b)


/* Map contained types to vector creation function */
#define TYPE_TO_VECTORS(post) \
    TYPE_TO_VECTOR(uint64_t, u64v, post), \
    TYPE_TO_VECTOR(int64_t, i64v, post), \
    TYPE_TO_VECTOR(uint32_t, u32v, post), \
    TYPE_TO_VECTOR(int32_t, i32v, post), \
    TYPE_TO_VECTOR(uint16_t, u16v, post), \
    TYPE_TO_VECTOR(int16_t, i16v, post), \
    TYPE_TO_VECTOR(uint8_t, u8v, post), \
    TYPE_TO_VECTOR(int8_t, i8v, post), \
    TYPE_TO_VECTOR(char*, strv, post), \
    TYPE_TO_VECTOR(void*, ptrv, post), \
    TYPE_TO_VECTOR(char**, char_ptr_ptrv, post), \
    TYPE_TO_VECTOR(short_string, short_str_v, post), \
    TYPE_TO_VECTOR(i32v, i32vv, post)


#endif /* VECTOR_AUTOGEN_H */