#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

static JNIEnv *globalenv = 0;

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1lock(JNIEnv *env, jobject self, jlong addr, jint len) {
    const char *ptr = (char*) addr;
    int lock = mlock(ptr, len);
    return (jint)lock;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1lockall(JNIEnv *env, jobject self, jlong addr, jint len) {
    const char *ptr = (char*) addr;
    int lock = mlock(ptr, len);
    return (jint)lock;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1protect(JNIEnv *env, jobject self, jlong addr, jint len, jint prot) {
    void *ptr = (char*) addr;
    int mprot = mprotect(ptr, len, prot);
    return (jint)mprot;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1map__JIIIIJ(JNIEnv *env, jobject self, jlong filedes, jint len, jint prot, jint flags, jint fd, jlong off_t) {
    globalenv = env;

    void *file_des = (void*) filedes;
    void *mapped = (void*)mmap(file_des, len, prot, flags, fd, off_t);

    if (mapped == MAP_FAILED) {
        close(fd);
        return (jlong)NULL;
    }

    const jlong *ptr = (jlong*)mapped;
    return (jlong)ptr;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1map__Ljava_lang_String_2IIIJ(JNIEnv *env, jobject self, jstring filepath, jint len, jint prot, jint flags, jlong off_t) {
    globalenv = env;
    void *file_path = (void*)(*env)->GetStringUTFChars(env, filepath, 0);
    int fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0600);
    void *mapped = (void*)mmap(file_path, len, prot, flags, fd, off_t);

    if (mapped == MAP_FAILED) {
        close(fd);
        (*env)->ReleaseStringUTFChars(env, filepath, file_path);
        return (jlong)NULL;
    }

    const jlong *ptr = (jlong*)mapped;
    return (jlong)ptr;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1sync__JII(JNIEnv *env, jobject self, jlong addr, jint len, jint prot) {
    globalenv = env;
    void *mapped = (void*)addr;
    jint sync = (jint)msync(mapped, len, prot);
    return sync;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1sync__Ljava_lang_String_2II(JNIEnv *env, jobject self, jstring filepath, jint len, jint prot) {
    globalenv = env;
    void *file_path = (void*)(*env)->GetStringUTFChars(env, filepath, 0);
    jint sync = (jint)msync(file_path, len, prot);
    (*env)->ReleaseStringUTFChars(env, filepath, file_path);
    return sync;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unmap__JI(JNIEnv *env, jobject self, jlong addr, jint len) {
    globalenv = env;
    void *mapped = (void*)addr;
    jint unmapped = (jint)munmap(mapped, len);
    return unmapped;
}

JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unmap__Ljava_lang_String_2I(JNIEnv *env, jobject self, jstring filepath, jint len) {
    globalenv = env;

    void *file_path = (void*)(*env)->GetStringUTFChars(env, filepath, 0);
    jint unmapped = (jint)munmap(file_path, len);
    (*env)->ReleaseStringUTFChars(env, filepath, file_path);

    return unmapped;
}