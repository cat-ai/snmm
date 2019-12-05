#ifndef jni_byte_buf_H
#define jni_byte_buf_H

#ifndef uint8_t
#include <stdint.h>
#endif

#include "jni.h"
#include <stdlib.h>

typedef union {
    jfloat  value;
    uint8_t bytes[4];
} jfloat_t;

typedef union {
    jdouble value;
    uint8_t bytes[8];
} jdouble_t;

typedef enum {
    BYTE_ORDER_LITTLE_ENDIAN,
    BYTE_ORDER_BIG_ENDIAN
} native_byte_order_t;

#define TRUE 1
#define FALSE 0

typedef struct {
    uint8_t *array;
    size_t size;
    size_t pos;
    uint8_t is_big_endian;
} jni_bytebuf_t;

void jni_bytebuf_alloc(jni_bytebuf_t *jni_byte_buf, size_t size);
jni_bytebuf_t *jni_bytebuf_malloc(unsigned int size);
jni_bytebuf_t* jni_bytebuf_alloc_size(size_t size);
void jni_bytebuf_set_byte_order(jni_bytebuf_t *jni_byte_buf, size_t size, native_byte_order_t order);
void jni_bytebuf_free(jni_bytebuf_t *jni_byte_buf);
size_t jni_byte_buf_get_size(jni_bytebuf_t jni_byte_buf);
void jni_byte_buf_reset(jni_bytebuf_t *jni_byte_buf);
uint8_t* jni_byte_buf_get_array(jni_bytebuf_t jni_byte_buf);

jboolean get_jboolean(jni_bytebuf_t *jni_byte_buf);
jboolean get_jboolean_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jbyte get_jbyte(jni_bytebuf_t *jni_byte_buf);
jbyte get_jbyte_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jchar get_jchar(jni_bytebuf_t *jni_byte_buf);
jchar get_jchar_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jshort get_jshort(jni_bytebuf_t *jni_byte_buf);
jshort get_jshort_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jshort get_jshort_from_addr_at(jlong addr, size_t idx);
jint get_jint(jni_bytebuf_t *jni_byte_buf);
jint get_jint_at(uint8_t *array, size_t idx);
jint get_jint_from_addr_at(jlong addr, size_t idx);
jfloat get_jfloat(jni_bytebuf_t *jni_byte_buf);
jfloat get_jfloat_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jfloat get_jfloat_from_addr_at(jlong addr, size_t idx);
jlong get_jlong(jni_bytebuf_t *jni_byte_buf);
jlong get_jlong_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jlong get_jlong_from_addr_at(jlong addr, size_t idx);
jdouble get_jdouble(jni_bytebuf_t *jni_byte_buf);
jdouble get_jdouble_at(jni_bytebuf_t jni_byte_buf, size_t idx);
jdouble get_jdouble_from_addr_at(jlong addr, size_t idx);
char* get_jstring(jni_bytebuf_t *jni_byte_buf, size_t length);
char* get_jstring_at(jni_bytebuf_t jni_byte_buf, size_t idx, size_t length);


void add_jboolean(jni_bytebuf_t *jni_byte_buf, jboolean value);
void add_jboolean_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jboolean value);
void add_jbyte(jni_bytebuf_t *jni_byte_buf, jbyte value);
void add_jbyte_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jbyte value);
void add_jchar(jni_bytebuf_t *jni_byte_buf, jchar value);
void add_jchar_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jchar value);
void add_jshort(jni_bytebuf_t *jni_byte_buf, jshort value);
void add_jshort_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jshort value);
void add_jshort_to_addr_at(jlong addr, size_t idx, jshort value);
void add_jint(jni_bytebuf_t *jni_byte_buf, jint value);
void add_jint_at(uint8_t *array, size_t idx, jint value);
void add_jint_to_addr_at(jlong addr, size_t idx, jint value);
void add_jfloat(jni_bytebuf_t *jni_byte_buf, jfloat value);
void add_jfloat_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jfloat value);
void add_jfloat_to_addr_at(jlong addr, size_t idx, jfloat value);
void add_jlong(jni_bytebuf_t *jni_byte_buf, jlong value);
void add_jlong_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jlong value);
void add_jlong_to_addr_at(jlong addr, size_t idx, jlong value);
void add_jdouble(jni_bytebuf_t *jni_byte_buf, jdouble value);
void add_jdouble_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jdouble value);
void add_jdouble_to_addr_at(jlong addr, size_t idx, jdouble value);
void add_jstring(jni_bytebuf_t *jni_byte_buf, jstring value, size_t length);
void add_jstring_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jstring value, size_t length);

#endif