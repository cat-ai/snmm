#include "jni_bytebuf.h"

#include "jni.h"

#include <stdio.h>
#include <string.h>

static native_byte_order_t get_native_byte_order(void) {
    uint32_t i = 1;
    char* c = (char*) &i;
    native_byte_order_t order;

    if (*c) {
        order = BYTE_ORDER_LITTLE_ENDIAN;
    } else {
        order = BYTE_ORDER_BIG_ENDIAN;
    }

    return order;
}

//static native_byte_order_t IS_BIG_ENDIAN = get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN;

static jfloat jni_byte_buf_int_bits_to_jfloat(uint32_t value) {
    jfloat_t j_float;

    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        j_float.bytes[0] = value & 255;
        j_float.bytes[1] = value >> 8 & 255;
        j_float.bytes[2] = (value >> 16) & 255;
        j_float.bytes[3] = (value >> 24) & 255;
    } else {
        j_float.bytes[3] = value & 255;
        j_float.bytes[2] = (value >> 8) & 255;
        j_float.bytes[1] = (value >> 16) & 255;
        j_float.bytes[0] = (value >> 24) & 255;
    }
    return j_float.value;
}

jni_bytebuf_t *jni_bytebuf_malloc(unsigned int size) {
    jni_bytebuf_t *buf = (jni_bytebuf_t*)malloc(sizeof(*buf));

    if (buf) {
        buf->size = size;
        buf->pos = 0;
        buf->array = (uint8_t *)malloc(size * sizeof(uint8_t));
        buf->is_big_endian = get_native_byte_order();
    }

    if ((buf != NULL) && (size != 0) && ((buf->size == NULL) || (buf->array == NULL))) {
        free(buf->size);
        free(buf->array);
        free(buf->pos);
        buf = NULL;
    }

    return buf;
}

void jni_bytebuf_alloc(jni_bytebuf_t *jni_byte_buf, size_t size) {
    jni_byte_buf->size = size;
    jni_byte_buf->pos = 0;
    jni_byte_buf->array = (uint8_t*)malloc(size * sizeof(uint8_t));
    jni_byte_buf->is_big_endian = get_native_byte_order();
}

jni_bytebuf_t* jni_bytebuf_alloc_size(size_t size) {
    jni_bytebuf_t buffer;
    jni_bytebuf_t *jni_byte_buf = &buffer;

    jni_byte_buf->size = size;
    jni_byte_buf->pos = 0;
    jni_byte_buf->array = (uint8_t *)malloc(size * sizeof(uint8_t));
    jni_byte_buf->is_big_endian = get_native_byte_order();

    return jni_byte_buf;
}

void jni_bytebuf_set_byte_order(jni_bytebuf_t *jni_byte_buf,
                                size_t size,
                                native_byte_order_t order) {
    jni_byte_buf->size = size;
    jni_byte_buf->pos = 0;
    jni_byte_buf->array = (uint8_t *)malloc(size * sizeof(uint8_t));

    if (order == BYTE_ORDER_LITTLE_ENDIAN) {
        jni_byte_buf->is_big_endian = FALSE;
    } else {
        jni_byte_buf->is_big_endian = TRUE;
    }
}

void jni_bytebuf_free(jni_bytebuf_t *jni_byte_buf) {
    jni_byte_buf->size = 0;
    jni_byte_buf->pos = 0;
    free(jni_byte_buf->array);
}

size_t jni_byte_buf_get_size(jni_bytebuf_t jni_byte_buf) {
    return jni_byte_buf.size;
}

void jni_byte_buf_reset(jni_bytebuf_t *jni_byte_buf) {
    jni_byte_buf->pos = 0;
}

uint8_t *jni_byte_buf_get_array(jni_bytebuf_t jni_byte_buf) {
    return jni_byte_buf.array;
}

void add_jboolean(jni_bytebuf_t *jni_byte_buf, jboolean value) {
    return;
}
void add_jboolean_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jboolean value) {
    return;
}

void add_jbyte(jni_bytebuf_t *jni_byte_buf, jbyte value) {
    return;
}

void add_jbyte_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jbyte value) {
    return;
}


jboolean get_jboolean(jni_bytebuf_t *jni_byte_buf) {
    return (jboolean)1;
}

jboolean get_jboolean_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    return (jboolean)1;
}

jbyte get_jbyte(jni_bytebuf_t *jni_byte_buf) {
    return (jbyte)123;
}

jbyte get_jbyte_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    return (jbyte)123;
}

static jchar jni_byte_buf_get_jchar_l(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;

    uint8_t b1 = array[jni_byte_buf->pos + 1];
    uint8_t b0 = array[jni_byte_buf->pos];

    jni_byte_buf->pos += 2;

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

static jchar jni_byte_buf_get_jchar_b(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;

    uint8_t b0 = array[jni_byte_buf->pos + 1];
    uint8_t b1 = array[jni_byte_buf->pos];

    jni_byte_buf->pos += 2;

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

jchar get_jchar(jni_bytebuf_t *jni_byte_buf) {
    jchar res = '\0';
    if (jni_byte_buf->is_big_endian) {
        res = jni_byte_buf_get_jchar_b(jni_byte_buf);
    } else {
        res = jni_byte_buf_get_jchar_l(jni_byte_buf);
    }
    return res;
}

static jchar jni_byte_buf_get_jchar_l_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

static jchar jni_byte_buf_get_jchar_b_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b0 = array[idx + 1];
    uint8_t b1 = array[idx];

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

jchar get_jchar_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    jchar res = '\0';
    if (jni_byte_buf.is_big_endian) {
        res = jni_byte_buf_get_jchar_b_at(jni_byte_buf, idx);
    } else {
        res = jni_byte_buf_get_jchar_l_at(jni_byte_buf, idx);
    }
    return res;
}

static jchar jni_byte_buf_get_jchar_from_addr_l_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

static jchar jni_byte_buf_get_jchar_from_addr_b_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b0 = array[idx + 1];
    uint8_t b1 = array[idx];

    return (jchar)((b1 & 255) << 8) | (b0 & 255);
}

jshort get_jchar_from_addr_at(jlong addr, size_t idx) {
    jchar res = '\0';
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        res = jni_byte_buf_get_jchar_from_addr_b_at(addr, idx);
    } else {
        res = jni_byte_buf_get_jchar_from_addr_l_at(addr, idx);
    }
    return res;
}

static jshort jni_byte_buf_get_jshort_l(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;

    uint8_t b1 = array[jni_byte_buf->pos + 1];
    uint8_t b0 = array[jni_byte_buf->pos];

    jni_byte_buf->pos += 2;

    return ((b1 & 255) << 8) | (b0 & 255);
}

static jshort jni_byte_buf_get_jshort_b(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;

    uint8_t b0 = array[jni_byte_buf->pos + 1];
    uint8_t b1 = array[jni_byte_buf->pos];

    jni_byte_buf->pos += 2;

    return ((b1 & 255) << 8) | (b0 & 255);
}

jshort get_jshort(jni_bytebuf_t *jni_byte_buf) {
    jshort res = 0;
    if (jni_byte_buf->is_big_endian) {
        res = jni_byte_buf_get_jshort_b(jni_byte_buf);
    } else {
        res = jni_byte_buf_get_jshort_l(jni_byte_buf);
    }
    return res;
}

static jshort jni_byte_buf_get_jshort_l_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return ((b1 & 255) << 8) | (b0 & 255);
}

static uint16_t jni_byte_buf_get_jshort_b_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b0 = array[idx + 1];
    uint8_t b1 = array[idx];

    return ((b1 & 255) << 8) | (b0 & 255);
}

jshort get_jshort_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    jshort res = 0;
    if (jni_byte_buf.is_big_endian) {
        res = jni_byte_buf_get_jshort_b_at(jni_byte_buf, idx);
    } else {
        res = jni_byte_buf_get_jshort_l_at(jni_byte_buf, idx);
    }
    return res;
}

static jshort jni_byte_buf_get_jshort_from_addr_l_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return ((b1 & 255) << 8) | (b0 & 255);
}

static jshort jni_byte_buf_get_jshort_from_addr_b_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b0 = array[idx + 1];
    uint8_t b1 = array[idx];

    return ((b1 & 255) << 8) | (b0 & 255);
}

jshort get_jshort_from_addr_at(jlong addr, size_t idx) {
    jshort res = 0;
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        res = jni_byte_buf_get_jshort_from_addr_b_at(addr, idx);
    } else {
        res = jni_byte_buf_get_jshort_from_addr_l_at(addr, idx);
    }
    return res;
}

static jint jni_byte_buf_get_jint_l(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;

    uint8_t b3 = array[jni_byte_buf->pos + 3];
    uint8_t b2 = array[jni_byte_buf->pos + 2];
    uint8_t b1 = array[jni_byte_buf->pos + 1];
    uint8_t b0 = array[jni_byte_buf->pos];

    jni_byte_buf->pos += 4;

    return (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);
}

static jint jni_byte_buf_get_jint_b(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    uint8_t b0 = array[pos + 3];
    uint8_t b1 = array[pos + 2];
    uint8_t b2 = array[pos + 1];
    uint8_t b3 = array[pos];

    jni_byte_buf->pos += 4;

    return (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);
}

jint get_jint(jni_bytebuf_t *jni_byte_buf) {
    jint res = 0;
    if (jni_byte_buf->is_big_endian) {
        res = jni_byte_buf_get_jint_b(jni_byte_buf);
    } else {
        res = jni_byte_buf_get_jint_l(jni_byte_buf);
    }
    return res;
}

static jint jni_byte_buf_get_jint_l_at(uint8_t *array, size_t idx) {

    uint8_t b3 = array[idx + 3];
    uint8_t b2 = array[idx + 2];
    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    jint j_value = (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);

    return j_value;
}

static jint jni_byte_buf_get_jint_b_at(uint8_t *array, size_t idx) {
    uint8_t b0 = array[idx + 3];
    uint8_t b1 = array[idx + 2];
    uint8_t b2 = array[idx + 1];
    uint8_t b3 = array[idx];

    jint j_value = (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);

    return j_value;
}

jint get_jint_at(uint8_t *array, size_t idx) {
    jint res = 0;
    native_byte_order_t is_big_endian = get_native_byte_order();
    if (is_big_endian) {
        res = jni_byte_buf_get_jint_b_at(array, idx);
    } else {
        res = jni_byte_buf_get_jint_l_at(array, idx);
    }
    return res;
}

static jint jni_byte_buf_get_jint_from_addr_l_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t*) addr;

    uint8_t b3 = array[idx + 3];
    uint8_t b2 = array[idx + 2];
    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    jint j_value = (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);

    return j_value;
}

static jint jni_byte_buf_get_jint_from_addr_b_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t*) addr;

    uint8_t b0 = array[idx + 3];
    uint8_t b1 = array[idx + 2];
    uint8_t b2 = array[idx + 1];
    uint8_t b3 = array[idx];

    jint j_value =  (b3 << 24) | ((b2 & 255) << 16) | ((b1 & 255) << 8) | (b0 & 255);

    return j_value;
}

jint get_jint_from_addr_at(jlong addr, size_t idx) {
    jint res = 0;
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        res = jni_byte_buf_get_jint_from_addr_b_at(addr, idx);
    } else {
        res = jni_byte_buf_get_jint_from_addr_l_at(addr, idx);
    }
    return res;
}

jfloat get_jfloat(jni_bytebuf_t *jni_byte_buf) {
    return jni_byte_buf_int_bits_to_jfloat(get_jint(jni_byte_buf));
}

jfloat get_jfloat_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    return jni_byte_buf_int_bits_to_jfloat(get_jint_at(jni_byte_buf.array, idx));
}

jfloat get_jfloat_from_addr_at(jlong addr, size_t idx) {
    return jni_byte_buf_int_bits_to_jfloat(get_jint_from_addr_at(addr, idx));
}

static jlong jni_byte_buf_get_jlong_l(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    uint8_t b7 = array[pos + 7];
    uint8_t b6 = array[pos + 6];
    uint8_t b5 = array[pos + 5];
    uint8_t b4 = array[pos + 4];
    uint8_t b3 = array[pos + 3];
    uint8_t b2 = array[pos + 2];
    uint8_t b1 = array[pos + 1];
    uint8_t b0 = array[pos];

    jni_byte_buf->pos += 8;

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ((jlong) b0 & 255);
}

static jlong jni_byte_buf_get_jlong_b(jni_bytebuf_t *jni_byte_buf) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    uint8_t b0 = array[pos + 7];
    uint8_t b1 = array[pos + 6];
    uint8_t b2 = array[pos + 5];
    uint8_t b3 = array[pos + 4];
    uint8_t b4 = array[pos + 3];
    uint8_t b5 = array[pos + 2];
    uint8_t b6 = array[pos + 1];
    uint8_t b7 = array[pos];

    jni_byte_buf->pos += 8;

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ((jlong) b0 & 255);
}

jlong get_jlong(jni_bytebuf_t *jni_byte_buf) {
    uint64_t res = 0;
    if (jni_byte_buf->is_big_endian) {
        res = jni_byte_buf_get_jlong_b(jni_byte_buf);
    } else {
        res = jni_byte_buf_get_jlong_l(jni_byte_buf);
    }
    return res;
}

static jlong jni_byte_buf_get_jlong_l_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b7 = array[idx + 7];
    uint8_t b6 = array[idx + 6];
    uint8_t b5 = array[idx + 5];
    uint8_t b4 = array[idx + 4];
    uint8_t b3 = array[idx + 3];
    uint8_t b2 = array[idx + 2];
    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ((jlong) b0 & 255);
}

static jlong jni_byte_buf_get_jlong_b_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint8_t *array = jni_byte_buf.array;

    uint8_t b0 = array[idx + 7];
    uint8_t b1 = array[idx + 6];
    uint8_t b2 = array[idx + 5];
    uint8_t b3 = array[idx + 4];
    uint8_t b4 = array[idx + 3];
    uint8_t b5 = array[idx + 2];
    uint8_t b6 = array[idx + 1];
    uint8_t b7 = array[idx];

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ( (jlong) b0 & 255);
}

jlong get_jlong_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    uint64_t res = 0;
    if (jni_byte_buf.is_big_endian) {
        res = jni_byte_buf_get_jlong_b_at(jni_byte_buf, idx);
    } else {
        res = jni_byte_buf_get_jlong_l_at(jni_byte_buf, idx);
    }
    return res;
}

static jlong jni_byte_buf_get_jlong_from_addr_l_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b7 = array[idx + 7];
    uint8_t b6 = array[idx + 6];
    uint8_t b5 = array[idx + 5];
    uint8_t b4 = array[idx + 4];
    uint8_t b3 = array[idx + 3];
    uint8_t b2 = array[idx + 2];
    uint8_t b1 = array[idx + 1];
    uint8_t b0 = array[idx];

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ((jlong) b0 & 255);
}

static jlong jni_byte_buf_get_jlong_from_addr_b_at(jlong addr, size_t idx) {
    uint8_t *array = (uint8_t *) addr;

    uint8_t b0 = array[idx + 7];
    uint8_t b1 = array[idx + 6];
    uint8_t b2 = array[idx + 5];
    uint8_t b3 = array[idx + 4];
    uint8_t b4 = array[idx + 3];
    uint8_t b5 = array[idx + 2];
    uint8_t b6 = array[idx + 1];
    uint8_t b7 = array[idx];

    return (((jlong) b7 & 255) << 56) | (((jlong) b6 & 255) << 48) |
           (((jlong) b5 & 255) << 40) | (((jlong) b4 & 255) << 32) |
           (((jlong) b3 & 255) << 24) | (((jlong) b2 & 255) << 16) |
           (((jlong) b1 & 255) << 8) | ( (jlong) b0 & 255);
}

jlong get_jlong_from_addr_at(jlong addr, size_t idx) {
    uint64_t res = 0;
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        res = jni_byte_buf_get_jlong_from_addr_b_at(addr, idx);
    } else {
        res = jni_byte_buf_get_jlong_from_addr_l_at(addr, idx);
    }
    return res;
}

static jdouble jni_byte_buf_get_jdouble_l(jni_bytebuf_t *jni_byte_buf) {
    jdouble_t j_double;

    for (int i = 0; i < 8; i++) {
        size_t pos = jni_byte_buf->pos++;
        uint8_t *storage = jni_byte_buf->array;
        j_double.bytes[i] = storage[pos];
    }

    return j_double.value;
}

static jdouble jni_byte_buf_get_jdouble_b(jni_bytebuf_t *jni_byte_buf) {
    jdouble_t j_double;

    for (int i = 7; i >= 0; i--) {
        size_t pos = jni_byte_buf->pos++;
        uint8_t *storage = jni_byte_buf->array;
        j_double.bytes[i] = storage[pos];
    }

    return j_double.value;
}

jdouble get_jdouble(jni_bytebuf_t *jni_byte_buf) {
    double res = 0;
    if (jni_byte_buf->is_big_endian) {
        res = jni_byte_buf_get_jdouble_b(jni_byte_buf);
    } else {
        res = jni_byte_buf_get_jdouble_l(jni_byte_buf);
    }
    return res;
}

static jdouble jni_byte_buf_get_jdouble_l_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    jdouble_t j_double;

    for (int i = 0; i < 8; i++) {
        size_t pos = idx++;
        uint8_t *storage = jni_byte_buf.array;
        j_double.bytes[i] = storage[pos];
    }

    return j_double.value;
}

static jdouble jni_byte_buf_get_jdouble_b_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    jdouble_t j_double;

    for (int i = 7; i >= 0; i--) {
        size_t pos = idx++;
        uint8_t *storage = jni_byte_buf.array;
        j_double.bytes[i] = storage[pos];
    }

    return j_double.value;
}

double get_jdouble_at(jni_bytebuf_t jni_byte_buf, size_t idx) {
    double res = 0;
    if (jni_byte_buf.is_big_endian) {
        res = jni_byte_buf_get_jdouble_b_at(jni_byte_buf, idx);
    } else {
        res = jni_byte_buf_get_jdouble_l_at(jni_byte_buf, idx);
    }
    return res;
}

static jdouble jni_byte_buf_get_jdouble_from_addr_l_at(jlong addr, size_t idx) {
    jdouble_t j_double;

    for (int i = 0; i < 8; i++) {
        size_t pos = idx++;
        uint8_t *arr = (uint8_t *) addr;
        j_double.bytes[i] = arr[pos];
    }

    return j_double.value;
}

static jdouble jni_byte_buf_get_jdouble_from_addr_b_at(jlong addr, size_t idx) {
    jdouble_t j_double;

    for (int i = 7; i >= 0; i--) {
        size_t pos = idx++;
        uint8_t *arr = (uint8_t *) addr;
        j_double.bytes[i] = arr[pos];
    }

    return j_double.value;
}

jdouble get_jdouble_from_addr_at(jlong addr, size_t idx) {
    jdouble res = 0;
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        res = jni_byte_buf_get_jdouble_from_addr_b_at(addr, idx);
    } else {
        res = jni_byte_buf_get_jdouble_from_addr_l_at(addr, idx);
    }
    return res;
}

static char *jni_byte_buf_get_jstring_l(jni_bytebuf_t *jni_byte_buf, size_t length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        size_t pos = jni_byte_buf->pos++;
        uint8_t *arr = jni_byte_buf->array;
        str[i] = arr[pos];
    }

    return str;
}

static char *jni_byte_buf_get_jstring_b(jni_bytebuf_t *jni_byte_buf, size_t length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        size_t pos = jni_byte_buf->pos++;
        uint8_t *arr = jni_byte_buf->array;
        str[i] = arr[pos];
    }
    return str;
}

char *get_jstring(jni_bytebuf_t *jni_byte_buf, size_t length) {
    char *str = NULL;

    if (jni_byte_buf->is_big_endian) {
        str = jni_byte_buf_get_jstring_b(jni_byte_buf, length);
    } else {
        str = jni_byte_buf_get_jstring_l(jni_byte_buf, length);
    }
    return str;
}

static jstring jni_byte_buf_get_jstring_l_at(jni_bytebuf_t jni_byte_buf, size_t idx, size_t length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++) {
        size_t pos = idx++;
        uint8_t *arr = jni_byte_buf.array;
        str[i] = arr[pos];
    }
    return str;
}

static jstring jni_byte_buf_get_jstring_b_at(jni_bytebuf_t jni_byte_buf, size_t idx, size_t length) {
    char *str = (char *) malloc(length * sizeof(char));

    for (int i = length - 1; i >= 0; i--) {
        size_t pos = idx++;
        uint8_t *arr = jni_byte_buf.array;
        str[i] = arr[pos];
    }
    return str;
}

char *get_jstring_at(jni_bytebuf_t jni_byte_buf, size_t idx, size_t length) {
    char *str = NULL;

    if (jni_byte_buf.is_big_endian) {
        str = jni_byte_buf_get_jstring_b_at(jni_byte_buf, idx, length);
    } else {
        str = jni_byte_buf_get_jstring_l_at(jni_byte_buf, idx, length);
    }
    return str;
}

/*
 * Put methods
 */

static void jni_byte_buf_write_jchar_l(jni_bytebuf_t *jni_byte_buf, jchar value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = value & 255;
    array[pos] = (value >> 8) & 255;
}

static void jni_byte_buf_write_jchar_b(jni_bytebuf_t *jni_byte_buf, jchar value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = (value >> 8) & 255;
    array[pos] = value & 255;
}

void add_jchar(jni_bytebuf_t *jni_byte_buf, jchar value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jchar_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jchar_l(jni_byte_buf, value);
    }
}

static void jni_byte_buf_write_jchar_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jchar value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = value & 255;
    array[idx] = (value >> 8) & 255;
}

static void jni_byte_buf_write_jchar_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jchar value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jchar_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jchar value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jchar_b_at(jni_byte_buf, idx, value);
    } else {
        jni_byte_buf_write_jchar_l_at(jni_byte_buf, idx, value);
    }
}

static void jni_byte_buf_write_jshort_l(jni_bytebuf_t *jni_byte_buf, jshort value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = value & 255;
    array[pos] = (value >> 8) & 255;
}

static void jni_byte_buf_write_jshort_b(jni_bytebuf_t *jni_byte_buf, jshort value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = (value >> 8) & 255;
    array[pos] = value & 255;
}

void add_jshort(jni_bytebuf_t *jni_byte_buf, jshort value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jshort_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jshort_l(jni_byte_buf, value);
    }
}

static void jni_byte_buf_write_jshort_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jshort value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = value & 255;
    array[idx] = (value >> 8) & 255;
}

static void jni_byte_buf_write_jshort_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jshort value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jshort_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jshort value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jshort_b_at(jni_byte_buf, idx, value);
    } else {
        jni_byte_buf_write_jshort_l_at(jni_byte_buf, idx, value);
    }
}

static void jni_byte_buf_write_jshort_to_addr_l_at(jlong addr, size_t idx, jshort value) {
    uint8_t *array = (uint8_t *) addr;

    array[idx++] = value & 255;
    array[idx] = (value >> 8) & 255;
}

static void jni_byte_buf_write_jshort_to_addr_b_at(jlong addr, size_t idx, jshort value) {
    uint8_t *array = (uint8_t *) addr;

    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jshort_to_addr_at(jlong addr, size_t idx, jshort value) {
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        jni_byte_buf_write_jshort_to_addr_b_at(addr, idx, value);
    } else {
        jni_byte_buf_write_jshort_to_addr_l_at(addr, idx, value);
    }
}

static void jni_byte_buf_write_jint_l(jni_bytebuf_t *jni_byte_buf, jint value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = value & 255;
    array[pos++] = (value >> 8) & 255;
    array[pos++] = (value >> 16) & 255;
    array[pos] = (value >> 24) & 255;
}

static void jni_byte_buf_write_jint_b(jni_bytebuf_t *jni_byte_buf, jint value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = (value >> 24) & 255;
    array[pos++] = (value >> 16) & 255;
    array[pos++] = (value >> 8) & 255;
    array[pos] = value & 255;
}

void add_jint(jni_bytebuf_t *jni_byte_buf, int32_t value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jint_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jint_l(jni_byte_buf, value);
    }
}

static void jni_byte_buf_write_jint_l_at(uint8_t *array, size_t idx, jint value) {

    array[idx++] = value & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx] = (value >> 24) & 255;
}

static void jni_byte_buf_write_jint_b_at(uint8_t *array, size_t idx, jint value) {

    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}


void add_jint_at(uint8_t *array, size_t idx, jint value) {
    if (get_native_byte_order()) {
        jni_byte_buf_write_jint_b_at(array, idx, value);
    } else {
        jni_byte_buf_write_jint_l_at(array, idx, value);
    }
}

static void jni_byte_buf_write_jint_to_addr_l_at(jlong addr, size_t idx, jint value) {
    uint8_t *array = (uint8_t *) addr;

    array[idx++] = value & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx] = (value >> 24) & 255;
}

static void jni_byte_buf_write_jint_to_addr_b_at(jlong addr, size_t idx, jint value) {
    uint8_t *array = (uint8_t*) addr;

    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jint_to_addr_at(jlong addr, size_t idx, jint value) {
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        jni_byte_buf_write_jint_to_addr_b_at(addr, idx, value);
    } else {
        jni_byte_buf_write_jint_to_addr_l_at(addr, idx, value);
    }
}

static void jni_byte_buf_write_jfloat_l(jni_bytebuf_t *jni_byte_buf, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = j_float.bytes[0];
    array[pos++] = j_float.bytes[1];
    array[pos++] = j_float.bytes[2];
    array[pos] = j_float.bytes[3];
}

static void jni_byte_buf_write_jfloat_b(jni_bytebuf_t *jni_byte_buf, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = j_float.bytes[3];
    array[pos++] = j_float.bytes[2];
    array[pos++] = j_float.bytes[1];
    array[pos] = j_float.bytes[0];
}

void add_jfloat(jni_bytebuf_t *jni_byte_buf, jfloat value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jfloat_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jfloat_l(jni_byte_buf, value);
    }
}

static void jni_byte_buf_write_jfloat_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = jni_byte_buf->array;

    array[idx++] = j_float.bytes[0];
    array[idx++] = j_float.bytes[1];
    array[idx++] = j_float.bytes[2];
    array[idx]   = j_float.bytes[3];
}

static void jni_byte_buf_write_jfloat_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = jni_byte_buf->array;

    array[idx++] = j_float.bytes[3];
    array[idx++] = j_float.bytes[2];
    array[idx++] = j_float.bytes[1];
    array[idx]   = j_float.bytes[0];
}

void add_jfloat_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jfloat value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jfloat_b_at(jni_byte_buf, idx, value);
    } else {
        jni_byte_buf_write_jfloat_l_at(jni_byte_buf, idx, value);
    }
}

static void jni_byte_buf_write_jfloat_to_addr_l_at(jlong addr, size_t idx, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = (uint8_t *) addr;

    array[idx++] = j_float.bytes[0];
    array[idx++] = j_float.bytes[1];
    array[idx++] = j_float.bytes[2];
    array[idx]   = j_float.bytes[3];
}

static void jni_byte_buf_write_jfloat_to_addr_b_at(jlong addr, size_t idx, jfloat value) {
    jfloat_t j_float;
    j_float.value = value;

    uint8_t *array = (uint8_t *) addr;

    array[idx++] = j_float.bytes[3];
    array[idx++] = j_float.bytes[2];
    array[idx++] = j_float.bytes[1];
    array[idx]   = j_float.bytes[0];
}

void add_jfloat_to_addr_at(jlong addr, size_t idx, jfloat value) {
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        jni_byte_buf_write_jfloat_to_addr_b_at(addr, idx, value);
    } else {
        jni_byte_buf_write_jfloat_to_addr_l_at(addr, idx, value);
    }
}

static void jni_byte_buf_write_jlong_l(jni_bytebuf_t *jni_byte_buf, jlong value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = value & 255;
    array[pos++] = (value >> 8) & 255;
    array[pos++] = (value >> 16) & 255;
    array[pos++] = (value >> 24) & 255;
    array[pos++] = (value >> 32) & 255;
    array[pos++] = (value >> 40) & 255;
    array[pos++] = (value >> 48) & 255;
    array[pos] = (value >> 56) & 255;
}

static void jni_byte_buf_write_jlong_b(jni_bytebuf_t *jni_byte_buf, jlong value) {
    uint8_t *array = jni_byte_buf->array;
    size_t pos = jni_byte_buf->pos;

    array[pos++] = (value >> 56) & 255;
    array[pos++] = (value >> 48) & 255;
    array[pos++] = (value >> 40) & 255;
    array[pos++] = (value >> 32) & 255;
    array[pos++] = (value >> 24) & 255;
    array[pos++] = (value >> 16) & 255;
    array[pos++] = (value >> 8) & 255;
    array[pos] = value & 255;
}

void add_jlong(jni_bytebuf_t *jni_byte_buf, jlong value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jlong_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jlong_l(jni_byte_buf, value);
    }
}

static void jni_byte_buf_write_jlong_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jlong value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = value & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 32) & 255;
    array[idx++] = (value >> 40) & 255;
    array[idx++] = (value >> 48) & 255;
    array[idx]   = (value >> 56) & 255;
}

static void jni_byte_buf_write_jlong_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jlong value) {
    uint8_t *array = jni_byte_buf->array;

    array[idx++] = (value >> 56) & 255;
    array[idx++] = (value >> 48) & 255;
    array[idx++] = (value >> 40) & 255;
    array[idx++] = (value >> 32) & 255;
    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jlong_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jlong value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jlong_b_at(jni_byte_buf, idx, value);
    } else {
        jni_byte_buf_write_jlong_l_at(jni_byte_buf, idx, value);
    }
}

static void jni_byte_buf_write_jlong_to_addr_l_at(jlong addr, size_t idx, jlong value) {
    uint8_t *array = (uint8_t *) addr;

    array[idx++] = value & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 32) & 255;
    array[idx++] = (value >> 40) & 255;
    array[idx++] = (value >> 48) & 255;
    array[idx]   = (value >> 56) & 255;
}

static void jni_byte_buf_write_jlong_to_addr_b_at(jlong addr, size_t idx, jlong value) {
    uint8_t *array = (uint8_t *) addr;

    array[idx++] = (value >> 56) & 255;
    array[idx++] = (value >> 48) & 255;
    array[idx++] = (value >> 40) & 255;
    array[idx++] = (value >> 32) & 255;
    array[idx++] = (value >> 24) & 255;
    array[idx++] = (value >> 16) & 255;
    array[idx++] = (value >> 8) & 255;
    array[idx] = value & 255;
}

void add_jlong_to_addr_at(jlong addr, size_t idx, jlong value) {
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        jni_byte_buf_write_jlong_to_addr_b_at(addr, idx, value);
    } else {
        jni_byte_buf_write_jlong_to_addr_l_at(addr, idx, value);
    }
}

static void jni_byte_buf_write_jdouble_l(jni_bytebuf_t *jni_byte_buf, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 0; i < 8; i++) {
        size_t cur_pos = jni_byte_buf->pos++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = j_double.bytes[i];
    }
}

static void jni_byte_buf_write_jdouble_b(jni_bytebuf_t *jni_byte_buf, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 7; i >= 0; i--) {
        size_t cur_pos = jni_byte_buf->pos++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = j_double.bytes[i];
    }
}

void add_jdouble(jni_bytebuf_t *jni_byte_buf, jdouble value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jdouble_b(jni_byte_buf, value);
    } else {
        jni_byte_buf_write_jdouble_l(jni_byte_buf, value);
    }
}

void jni_byte_buf_write_jdouble_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 0; i < 8; i++) {
        size_t cur_pos = idx++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = j_double.bytes[i];
    }
}

void jni_byte_buf_write_jdouble_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 7; i >= 0; i--) {
        size_t cur_pos = idx++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = j_double.bytes[i];
    }
}

void add_jdouble_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jdouble value) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jdouble_b_at(jni_byte_buf, idx, value);
    } else {
        jni_byte_buf_write_jdouble_l_at(jni_byte_buf, idx, value);
    }
}

void jni_byte_buf_write_jdouble_to_addr_l_at(jlong addr, size_t idx, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 0; i < 8; i++) {
        size_t cur_pos = idx++;
        uint8_t *storage = (uint8_t *) addr;
        storage[cur_pos] = j_double.bytes[i];
    }
}

void jni_byte_buf_write_jdouble_to_addr_b_at(jlong addr, size_t idx, jdouble value) {
    jdouble_t j_double;
    j_double.value = value;

    for (int i = 7; i >= 0; i--) {
        size_t cur_pos = idx++;
        uint8_t *storage = (uint8_t *) addr;
        storage[cur_pos] = j_double.bytes[i];
    }
}

void add_jdouble_to_addr_at(jlong addr, size_t idx, jdouble value) {
    if (get_native_byte_order() == BYTE_ORDER_BIG_ENDIAN) {
        jni_byte_buf_write_jdouble_to_addr_b_at(addr, idx, value);
    } else {
        jni_byte_buf_write_jdouble_to_addr_l_at(addr, idx, value);
    }
}

static void jni_byte_buf_write_jstring_l(jni_bytebuf_t *jni_byte_buf, const char *value, size_t length) {
    for (int i = 0; i < length; i++) {
        size_t cur_pos = jni_byte_buf->pos++;
        uint8_t* storage = jni_byte_buf->array;
        storage[cur_pos] = value[i];
    }
}

static void jni_byte_buf_write_jstring_b(jni_bytebuf_t *jni_byte_buf, const char *value, size_t length) {
    for (int i = length - 1; i >= 0; i--) {
        size_t cur_pos = jni_byte_buf->pos++;
        uint8_t* storage = jni_byte_buf->array;
        storage[cur_pos] = value[i];
    }
}

void add_jstring(jni_bytebuf_t *jni_byte_buf, jstring value, size_t length) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jstring_b(jni_byte_buf, value, length);
    } else {
        jni_byte_buf_write_jstring_l(jni_byte_buf, value, length);
    }
}

static void jni_byte_buf_write_jstring_l_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jstring_value, size_t length) {
    for (int i = 0; i < length; i++) {
        size_t cur_pos = idx++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = jstring_value;
    }
}

static void jni_byte_buf_write_jstring_b_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jstring_value, size_t length) {
    for (int i = length - 1; i >= 0; i--) {
        size_t cur_pos = idx++;
        uint8_t *storage = jni_byte_buf->array;
        storage[cur_pos] = jstring_value;
    }
}

void add_jstring_at(jni_bytebuf_t *jni_byte_buf, size_t idx, jstring value, size_t length) {
    if (jni_byte_buf->is_big_endian) {
        jni_byte_buf_write_jstring_b_at(jni_byte_buf, idx, value, length);
    } else {
        jni_byte_buf_write_jstring_l_at(jni_byte_buf, idx, value, length);
    }
}