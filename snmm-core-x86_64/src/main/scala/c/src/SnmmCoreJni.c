#include "jni.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "util/hashmap.h"

static JNIEnv* globalenv = 0;

static const char* JBOOLEAN_LIT = "JBoolean";
static const char* JBYTE_LIT = "JByte";
static const char* JCHAR_LIT = "JChar";
static const char* JSHORT_LIT = "JShort";
static const char* JINT_LIT = "JInt";
static const char* JFLOAT_LIT = "JFloat";
static const char* JDOUBLE_LIT = "JDouble";
static const char* JLONG_LIT = "JLong";
static const char* JSTRING_LIT = "JString";

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_integer_1pointer(JNIEnv *env, jobject self, jint val) {
    globalenv = env;
    jint *ptr = (jint*)malloc(sizeof(jint));
    jint *val_ptr = &val;
    memcpy(ptr, val_ptr, sizeof(jint));
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_boolean_1pointer(JNIEnv *env, jobject self, jboolean val) {
    globalenv = env;
    jboolean *ptr = (jboolean*)malloc(sizeof(jboolean));
    jboolean *val_ptr = &val;
    memcpy(ptr, val_ptr, sizeof(jboolean));
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_byte_1pointer(JNIEnv *env, jobject self, jbyte val) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)malloc(sizeof(jbyte));
    jbyte *val_ptr = &val;
    j_byte_ptr = (jbyte*)memcpy(j_byte_ptr, val_ptr, sizeof(jbyte));
    return (jlong)j_byte_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_char_1pointer(JNIEnv *env, jobject self, jchar val) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)malloc(sizeof(jchar));
    jchar *val_ptr = &val;
    j_char_ptr = (jchar*)memcpy(j_char_ptr, val_ptr, sizeof(jchar));
    return (jlong)j_char_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_short_1pointer(JNIEnv * env, jobject self, jshort val) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)malloc(sizeof(jshort));
    jshort *val_ptr = &val;
    j_short_ptr = (jshort*)memcpy(j_short_ptr, val_ptr, sizeof(jshort));
    return (jlong)j_short_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_float_1pointer(JNIEnv *env, jobject self, jfloat val) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)malloc(sizeof(jfloat));
    jfloat *val_ptr = &val;
    j_float_ptr = (jfloat*)memcpy(j_float_ptr, val_ptr, sizeof(jfloat));
    return (jlong)j_float_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_long_1pointer(JNIEnv *env, jobject self, jlong val) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)malloc(sizeof(jlong));
    jlong *val_ptr = &val;
    j_long_ptr = (jlong*)memcpy(j_long_ptr, val_ptr, sizeof(jlong));
    return (jlong)j_long_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_double_1pointer(JNIEnv *env, jobject self, jdouble val) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)malloc(sizeof(jdouble));
    jdouble *ptr_val = &val;
    j_double_ptr = (jdouble*)memcpy(j_double_ptr, ptr_val, sizeof(jdouble));
    return (jlong)j_double_ptr;
}

static char *jstring_cpy_to_native_string(jstring val) {
    char *src = (*globalenv)->GetStringUTFChars(globalenv, val, 0);
    int len = strlen(src);
    char *dest = (char*)malloc((sizeof(char) * len));
    char *copied = (char*)strcpy(dest, src);

    (*globalenv)->ReleaseStringUTFChars(globalenv, val, src);

    return copied;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_string_1pointer(JNIEnv *env, jobject self, jstring val) {
    globalenv = env;

    char *native_chars = jstring_cpy_to_native_string(val);

    return (jlong)native_chars;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1byte(JNIEnv *env, jobject self, jlong ptr, jbyte val) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)ptr;
    *j_byte_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1boolean(JNIEnv *env, jobject self, jlong ptr, jboolean val) {
    globalenv = env;
    jboolean *j_bool_ptr = (jboolean*)ptr;
    *j_bool_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1char(JNIEnv *env, jobject self, jlong ptr, jchar val) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)ptr;
    *j_char_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1short(JNIEnv *env, jobject self, jlong ptr, jshort val) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)ptr;
    *j_short_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1integer(JNIEnv *env, jobject self, jlong ptr, jint val) {
    globalenv = env;
    jint *j_int_ptr = (jint*)ptr;
    *j_int_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1float(JNIEnv *env, jobject self, jlong ptr, jfloat val) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)ptr;
    *j_float_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1long(JNIEnv *env, jobject self, jlong ptr, jlong val) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)ptr;
    *j_long_ptr = val;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_assign_1double(JNIEnv *env, jobject self, jlong ptr, jdouble val) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)ptr;
    *j_double_ptr = val;
    return;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1boolean(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jboolean *j_bool_ptr = (jboolean*)ptr;
    jboolean j_bool_val = *j_bool_ptr;
    return j_bool_val;
}

JNIEXPORT jbyte JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1byte(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jbyte *j_byte_ptr = (jbyte*)ptr;
    jbyte j_byte_val = *j_byte_ptr;
    return j_byte_val;
}

JNIEXPORT jshort JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1short(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jshort *j_short_ptr = (jshort*)ptr;
    jshort j_short_val = *j_short_ptr;
    return j_short_val;
}

JNIEXPORT jchar JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1char(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jchar *j_char_ptr = (jchar*)ptr;
    jchar j_char_val = *j_char_ptr;
    return j_char_val;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1int(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jint *j_int_ptr = (jint*)ptr;
    jint j_int_val = *j_int_ptr;
    return j_int_val;
}

JNIEXPORT jfloat JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1float(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jfloat *j_float_ptr = (jfloat*)ptr;
    jfloat j_float_val = *j_float_ptr;
    return j_float_val;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1long(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jlong *j_long_ptr = (jlong*)ptr;
    jlong j_long_val = *j_long_ptr;
    return j_long_val;
}

JNIEXPORT jdouble JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1double(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    jdouble *j_double_ptr = (jdouble*)ptr;
    return (jlong)j_double_ptr;
}

JNIEXPORT jstring JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_deref_1string(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    char *chars = (char*) ptr;
    jstring j_string_val = (*env)->NewStringUTF(env, chars);

    return j_string_val;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_malloc(JNIEnv *env, jobject self, jint size) {
    globalenv = env;
    void *malloc_buffer = malloc(size);
    return (jlong)malloc_buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_calloc(JNIEnv *env, jobject self, jint n, jint size) {
    globalenv = env;
    void *calloc_buffer = calloc(n, size);
    return (jlong)calloc_buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_realloc(JNIEnv *env, jobject self, jlong ptr, jint size) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *realloc_buffer = realloc(c_ptr, size);
    return (jlong)realloc_buffer;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_free(JNIEnv *env, jobject self, jlong ptr) {
    void *c_ptr = (void*) ptr;
    free(c_ptr);
    return;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_boolean_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jboolean);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_char_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jchar);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_short_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jshort);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_int_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jint);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_byte_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jbyte);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_long_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jlong);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_float_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jfloat);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_double_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jdouble);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_string_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jstring);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_byte_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jbyte*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_char_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jchar*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_short_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jshort*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_int_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jint*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_float_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jfloat*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_long_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jlong*);
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_double_ptr_1size(JNIEnv *env, jobject self) {
    globalenv = env;
    return sizeof(jdouble*);
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_mem_1cpy(JNIEnv *env, jobject self, jlong str1, jlong str2, jint n) {
    globalenv = env;
    void *str1_ptr = (void*)str1;
    void *str2_ptr = (void*)str2;
    void *copied = memcpy(str1_ptr, str2_ptr, n);
    return (jlong)copied;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_mem_1move(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    void *c_ptr_1 = (void*)ptr;
    void *c_ptr_2 = (void*)ptr2;
    void *moved = memmove(c_ptr_1, c_ptr_2, n);
    return (jlong)moved;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_mem_1chr(JNIEnv *env, jobject self, jlong ptr, jint n, jint n2) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *buffer = memchr(c_ptr, n, n2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_mem_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    const void *c_ptr_1 = (void*)ptr;
    const void *c_ptr_2 = (void*)ptr2;
    int n_res = memcmp(c_ptr_1, c_ptr_2, n);
    return n_res;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_mem_1set(JNIEnv *env, jobject self, jlong ptr, jint n, jint n2) {
    globalenv = env;
    void *c_ptr = (void*)ptr;
    void *buffer = memset(c_ptr, n, n2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1cat(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strcat(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_strn_1cat(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strncat(c_ptr, c_ptr_2, n);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1chr(JNIEnv *env, jobject self, jlong ptr, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    char *buffer = strchr(c_ptr, n);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_strr_1chr(JNIEnv *env, jobject self, jlong ptr, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    char *buffer = strrchr(c_ptr, n);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n = strcmp(c_ptr, c_ptr_2);
    return n;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_strn_1cmp(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n_res = strncmp(c_ptr, c_ptr_2, n);
    return n_res;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1coll(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int n = strcoll(c_ptr, c_ptr_2);
    return n;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1cpy(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strcpy(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1len(JNIEnv *env, jobject self, jlong ptr) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    int size = strlen(c_ptr);
    return size;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1spn(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int size = strspn(c_ptr, c_ptr_2);
    return size;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1cspn(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int size = strcspn(c_ptr, c_ptr_2);
    return size;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1prbk(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    const char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strpbrk(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1str(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *haystack = (char*)ptr;
    const char* needle = (char*)ptr2;
    char *buffer = strstr(haystack, needle);
    return (jlong)buffer;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1tok(JNIEnv *env, jobject self, jlong ptr, jlong ptr2) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    char *buffer = strtok(c_ptr, c_ptr_2);
    return (jlong)buffer;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_str_1xfrm(JNIEnv *env, jobject self, jlong ptr, jlong ptr2, jint n) {
    globalenv = env;
    char *c_ptr = (char*)ptr;
    const char *c_ptr_2 = (char*)ptr2;
    int len = strxfrm(c_ptr, c_ptr_2, n);
    return len;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1alloc(JNIEnv *env, jobject self, jint size) {
    globalenv = env;

    hashmap_t *hashmap = hashmap_alloc(1 << 4);

    return (jlong)hashmap;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1byte_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jbyte *j_byte_ptr = malloc(sizeof(jbyte) * count);
    hashmap_put(hashmap, JBYTE_LIT, j_byte_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1char_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jchar *j_char_ptr = malloc(sizeof(jchar) * count);
    hashmap_put(hashmap, JCHAR_LIT, j_char_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1short_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jshort *j_short_ptr = malloc(sizeof(jshort) * count);
    hashmap_put(hashmap, JSHORT_LIT, j_short_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1int_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jint *j_int_ptr = (jint*)malloc(sizeof(jint) * count);
    hashmap_put(hashmap, JINT_LIT, j_int_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1float_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jfloat *j_float_ptr = (jfloat*)malloc(sizeof(jfloat) * count);
    hashmap_put(hashmap, JFLOAT_LIT, j_float_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1long_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jlong *j_long_ptr = (jlong*)malloc(sizeof(jlong) * count);
    hashmap_put(hashmap, JLONG_LIT, j_long_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1double_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jdouble *j_double_ptr = (jdouble*) malloc(sizeof(jdouble) * count);

    hashmap_put(hashmap, JDOUBLE_LIT, j_double_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1string_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    char **j_string_ptr = malloc(sizeof(j_string_ptr) * count);
    hashmap_put(hashmap, JSTRING_LIT, j_string_ptr);
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1pointer_1key(JNIEnv *env, jobject self, jint count, jlong struct_addr) {
    globalenv = env;
    return;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1free(JNIEnv *env, jobject self, jlong addr) {
    globalenv = env;
    hashmap_dealloc((hashmap_t*) addr);
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1boolean_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    // TODO
    return (jlong) 0;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1byte_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jbyte *j_byte_ptr = hashmap_get(hashmap, JBYTE_LIT);

    if (j_byte_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_byte_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1char_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jchar *j_char_ptr = hashmap_get(hashmap, JCHAR_LIT);

    if (j_char_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_char_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1short_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jshort *j_short_ptr = hashmap_get(hashmap, JSHORT_LIT);

    if (j_short_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_short_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1int_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jint *j_int_ptr = hashmap_get(hashmap, JINT_LIT);

    if (j_int_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_int_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1long_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jlong *j_long_ptr = hashmap_get(hashmap, JLONG_LIT);


    if (j_long_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_long_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1float_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jfloat *j_float_ptr = hashmap_get(hashmap, JFLOAT_LIT);

    if (j_float_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_float_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1double_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jdouble *j_double_ptr = hashmap_get(hashmap, JDOUBLE_LIT);

    if (j_double_ptr == NULL) {
        return (jlong) NULL;
    }

    return (jlong)j_double_ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1get_1string_1member(JNIEnv *env, jobject self, jint pos, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;
    jstring *j_string_ptr = hashmap_get(hashmap, JSTRING_LIT);
    return (jlong)0;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1boolean_1member(JNIEnv *env, jobject self, jboolean value, jint idx, jlong bytebuf_addr) {
    globalenv = env;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1byte_1member(JNIEnv *env, jobject self, jbyte value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jbyte *j_byte_ptr = hashmap_get(hashmap, JBYTE_LIT);

    j_byte_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1char_1member(JNIEnv *env, jobject self, jchar value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jchar *j_char_ptr = hashmap_get(hashmap, JCHAR_LIT);

    j_char_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1short_1member(JNIEnv *env, jobject self, jshort value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jshort *j_short_ptr = hashmap_get(hashmap, JSHORT_LIT);

    j_short_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1int_1member(JNIEnv *env, jobject self, jint value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jint *j_int_ptr = hashmap_get(hashmap, JINT_LIT);

    j_int_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1long_1member(JNIEnv *env, jobject self, jlong value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jlong *j_long_ptr = (jlong*)hashmap_get(hashmap, JLONG_LIT);

    j_long_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1float_1member(JNIEnv *env, jobject self, jfloat value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jfloat *j_float_ptr = hashmap_get(hashmap, JFLOAT_LIT);

    j_float_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1double_1member(JNIEnv *env, jobject self, jdouble value, jint idx, jlong struct_addr) {
    globalenv = env;

    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    jdouble *j_double_ptr = hashmap_get(hashmap, JDOUBLE_LIT);

    j_double_ptr[idx] = value;
}

JNIEXPORT void JNICALL Java_io_cat_ai_snmm_core_jni_SnmmCoreJni_struct_1put_1string_1member(JNIEnv *env, jobject self, jstring value, jint idx, jlong struct_addr) {
    globalenv = env;
    hashmap_t *hashmap = (hashmap_t*) struct_addr;

    char *jstring_ptr = hashmap_get(hashmap, JSTRING_LIT);
    char *j_string_ptr = jstring_cpy_to_native_string(value);

    j_string_ptr[idx] = j_string_ptr;
}