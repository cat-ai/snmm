#include <jni.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "util/jni_bytebuf.h"

static JNIEnv* globalenv = 0;

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_integer_1pointer(JNIEnv *env, jobject self, jint val) {
    globalenv = env;
    jint *ptr = (jint*)malloc(sizeof(jint));
    jint *val_ptr = &val;
    memcpy(ptr, val_ptr, sizeof(jint));
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_boolean_1pointer(JNIEnv *env, jobject self, jboolean val) {
    globalenv = env;
    jboolean *ptr = (jboolean*)malloc(sizeof(jboolean));
    jboolean *val_ptr = &val;
    memcpy(ptr, val_ptr, sizeof(jboolean));
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_byte_1pointer(JNIEnv *env, jobject self, jbyte val) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)malloc(sizeof(jbyte));
    jbyte *val_ptr = &val;
    j_byte_ptr = (jbyte*)memcpy(j_byte_ptr, val_ptr, sizeof(jbyte));
    return (jlong)j_byte_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_char_1pointer(JNIEnv *env, jobject self, jchar val) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)malloc(sizeof(jchar));
    jchar *val_ptr = &val;
    j_char_ptr = (jchar*)memcpy(j_char_ptr, val_ptr, sizeof(jchar));
    return (jlong)j_char_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_short_1pointer(JNIEnv * env, jobject self, jshort val) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)malloc(sizeof(jshort));
    jshort *val_ptr = &val;
    j_short_ptr = (jshort*)memcpy(j_short_ptr, val_ptr, sizeof(jshort));
    return (jlong)j_short_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_float_1pointer(JNIEnv *env, jobject self, jfloat val) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)malloc(sizeof(jfloat));
    jfloat *val_ptr = &val;
    j_float_ptr = (jfloat*)memcpy(j_float_ptr, val_ptr, sizeof(jfloat));
    return (jlong)j_float_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_long_1pointer(JNIEnv *env, jobject self, jlong val) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)malloc(sizeof(jlong));
    jlong *val_ptr = &val;
    j_long_ptr = (jlong*)memcpy(j_long_ptr, val_ptr, sizeof(jlong));
    return (jlong)j_long_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_double_1pointer(JNIEnv *env, jobject self, jdouble val) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)malloc(sizeof(jdouble));
    jdouble *ptr_val = &val;
    j_double_ptr = (jdouble*)memcpy(j_double_ptr, ptr_val, sizeof(jdouble));
    return (jlong)j_double_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_string_1pointer(JNIEnv * env, jobject self, jstring val) {
    globalenv = env;
    jstring *j_string_ptr = (jstring*)malloc(sizeof(jstring));
    jstring *val_ptr = &val;
    j_string_ptr = (jstring*)memcpy(j_string_ptr, val_ptr, sizeof(jstring));
    return (jlong)j_string_ptr;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1byte(JNIEnv *env, jobject self, jlong ptr, jbyte val) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)ptr;
    *j_byte_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1boolean(JNIEnv *env, jobject self, jlong ptr, jboolean val) {
    globalenv = env;
    jboolean *j_bool_ptr = (jboolean*)ptr;
    *j_bool_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1char(JNIEnv *env, jobject self, jlong ptr, jchar val) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)ptr;
    *j_char_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1short(JNIEnv *env, jobject self, jlong ptr, jshort val) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)ptr;
    *j_short_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1integer(JNIEnv *env, jobject self, jlong ptr, jint val) {
    globalenv = env;
    jint *j_int_ptr = (jint*)ptr;
    *j_int_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1float(JNIEnv *env, jobject self, jlong ptr, jfloat val) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)ptr;
    *j_float_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1long(JNIEnv *env, jobject self, jlong ptr, jlong val) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)ptr;
    *j_long_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_assign_1double(JNIEnv *env, jobject self, jlong ptr, jdouble val) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)ptr;
    *j_double_ptr = val;
    return;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1boolean(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jboolean *j_bool_ptr = (jboolean*)ptr;
    jboolean j_bool_val = *j_bool_ptr;
    return j_bool_val;
}

JNIEXPORT jbyte JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1byte(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)ptr;
    jbyte j_byte_val = *j_byte_ptr;
    return j_byte_val;
}

JNIEXPORT jshort JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1short(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)ptr;
    jshort j_short_val = *j_short_ptr;
    return j_short_val;
}

JNIEXPORT jchar JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1char(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)ptr;
    jchar j_char_val = *j_char_ptr;
    return j_char_val;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1int(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jint *j_int_ptr = (jint*)ptr;
    jint j_int_val = *j_int_ptr;
    return j_int_val;
}

JNIEXPORT jfloat JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1float(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)ptr;
    jfloat j_float_val = *j_float_ptr;
    return j_float_val;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1long(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)ptr;
    jlong j_long_val = *j_long_ptr;
    return j_long_val;
}

JNIEXPORT jdouble JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1double(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)ptr;
    return (jlong)j_double_ptr;
}

JNIEXPORT jstring JNICALL Java_io_cat_ai_platform_jni_c_1jni_deref_1string(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jstring *j_str_ptr = (jstring*)ptr;

//    const char *name = (*env)->GetStringUTFChars(env,string, NULL);
//
//    const char *str = (*env)->GetStringUTFChars(env, prompt, 0)
//    return *j_str_ptr;
    return *j_str_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_malloc(JNIEnv *env, jobject self, jint size) {
    globalenv = env;
    void *malloc_buffer = malloc(size);
    return (jlong)malloc_buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_calloc(JNIEnv *env, jobject self, jint n, jint size) {
    globalenv = env;
    void *calloc_buffer = calloc(n, size);
    return (jlong)calloc_buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_realloc(JNIEnv *env, jobject self, jlong ptr, jint size) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *realloc_buffer = realloc(c_ptr, size);
    return (jlong)realloc_buffer;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_free(JNIEnv *env, jobject self, jlong ptr) {
    void *c_ptr = (void*) ptr;
    free(c_ptr);
    return;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_boolean_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jboolean);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_char_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jchar);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_short_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jshort);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_int_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jint);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_byte_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jbyte);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_long_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jlong);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_float_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jfloat);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_double_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jdouble);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_string_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jstring);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_byte_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jbyte*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_char_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jchar*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_short_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jshort*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_int_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jint*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_float_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jfloat*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_long_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jlong*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_double_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jdouble*);
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_mem_1cpy(JNIEnv *env, jobject self, jlong str1, jlong str2, jint n) {
    globalenv = env;
    void *str1_ptr = (void*)str1;
    void *str2_ptr = (void*)str2;
    void *copied = memcpy(str1_ptr, str2_ptr, n);
    return (jlong)copied;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_mem_1move(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    void *c_ptr_1 = (void*)ptr;
    void *c_ptr_2 = (void*)ptr2;
    void *moved = memmove(c_ptr_1, c_ptr_2, n);
    return (jlong)moved;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_mem_1chr(JNIEnv *env, jobject self, jlong ptr, jint n, jint n2) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *buffer = memchr(c_ptr, n, n2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_mem_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    const void *c_ptr_1 = (void*)ptr;
    const void *c_ptr_2 = (void*)ptr2;
    int n_res = memcmp(c_ptr_1, c_ptr_2, n);
    return n_res;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_mem_1set(JNIEnv *env, jobject self, jlong ptr, jint n, jint n2) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *buffer = memset(c_ptr, n, n2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1cat(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strcat(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_strn_1cat(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strncat(c_ptr, c_ptr_2, n);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1chr(JNIEnv *env, jobject self, jlong ptr, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    char *buffer = strchr(c_ptr, n);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_strr_1chr(JNIEnv *env, jobject self, jlong ptr, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    char *buffer = strrchr(c_ptr, n);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n = strcmp(c_ptr, c_ptr_2);
    return n;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_strn_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n_res = strncmp(c_ptr, c_ptr_2, n);
    return n_res;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1coll(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n = strcoll(c_ptr, c_ptr_2);
    return n;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1cpy(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strcpy(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1len(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    int size = strlen(c_ptr);
    return size;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1spn(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int size = strspn(c_ptr, c_ptr_2);
    return size;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1cspn(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int size = strcspn(c_ptr, c_ptr_2);
    return size;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1prbk(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strpbrk(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1str(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *haystack = (char*)ptr;
    const char* needle = (char*)ptr2;
    char *buffer = strstr(haystack, needle);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1tok(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strtok(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_platform_jni_c_1jni_str_1xfrm(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int len = strxfrm(c_ptr, c_ptr_2, n);
    return len;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1alloc(JNIEnv *env, jobject self, jint size) {
    globalenv = env;

    jni_bytebuf_t jni_bytebuf;
    jni_bytebuf_alloc(&jni_bytebuf, (size_t) size);

    jlong addr = (jlong)jni_bytebuf.array;
    return addr;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1free(JNIEnv *env, jobject self, jlong addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) addr;
    free(jni_bytebuf);
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1boolean_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jboolean value = get_jboolean_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1byte_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jbyte value = get_jbyte_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1char_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jchar value = get_jchar_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1short_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jshort value = get_jshort_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1int_1member(JNIEnv *env, jobject self, jint idx, jlong bytebuf_addr) {
    globalenv = env;

    jint value = get_jint_from_addr_at(bytebuf_addr, idx);

    jint *ptr = (jint*)malloc(sizeof(jint));
    jint *val_ptr = &value;
    memcpy(ptr, val_ptr, sizeof(jint));
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1long_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jlong value = get_jlong_at(jni_bytebuf, 0);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1float_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jfloat value = get_jfloat_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1double_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jdouble value = get_jdouble_at(jni_bytebuf, pos);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1get_1string_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    jni_bytebuf_t jni_bytebuf = *(jni_bytebuf_t*)struct_addr;
    jstring value = get_jstring_at(jni_bytebuf, pos, (size_t) 8);
    jlong address = (jlong)&value;
    return address;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1boolean_1member(JNIEnv *env, jobject self, jboolean value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jint_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1byte_1member(JNIEnv *env, jobject self, jbyte value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jint_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1char_1member(JNIEnv *env, jobject self, jchar value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jint_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1short_1member(JNIEnv *env, jobject self, jshort value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jshort_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1int_1member(JNIEnv *env, jobject self, jint value, jint idx, jlong arr_addr) {
    globalenv = env;
    uint8_t *buf = (uint8_t*) arr_addr;

    add_jint_to_addr_at(arr_addr, idx, value);

    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1long_1member(JNIEnv *env, jobject self, jlong value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jlong_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1float_1member(JNIEnv *env, jobject self, jfloat value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jfloat_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1double_1member(JNIEnv *env, jobject self, jdouble value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jdouble_at(jni_bytebuf, idx, value);
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_platform_jni_c_1jni_struct_1put_1string_1member(JNIEnv *env, jobject self, jstring value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
    jni_bytebuf_t *jni_bytebuf = (jni_bytebuf_t*) bytebuf_addr;
    add_jstring_at(jni_bytebuf, idx, value, (size_t) 8);
    return;
}