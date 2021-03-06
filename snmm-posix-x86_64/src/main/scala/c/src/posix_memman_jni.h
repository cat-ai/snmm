/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class io_cat_ai_jni_posix_memman_jni */

#ifndef _Included_io_cat_ai_jni_posix_memman_jni
#define _Included_io_cat_ai_jni_posix_memman_jni
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_lock
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1lock
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_lockall
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1lockall
  (JNIEnv *, jobject, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_map
 * Signature: (JIIIIJ)J
 */
JNIEXPORT jlong JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1map__JIIIIJ
  (JNIEnv *, jobject, jlong, jint, jint, jint, jint, jlong);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_map
 * Signature: (Ljava/lang/String;IIIJ)J
 */
JNIEXPORT jlong JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1map__Ljava_lang_String_2IIIJ
  (JNIEnv *, jobject, jstring, jint, jint, jint, jlong);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_protect
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1protect
  (JNIEnv *, jobject, jlong, jint, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_sync
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1sync__JII
  (JNIEnv *, jobject, jlong, jint, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_sync
 * Signature: (Ljava/lang/String;II)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1sync__Ljava_lang_String_2II
  (JNIEnv *, jobject, jstring, jint, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_unlock
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unlock__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_unlock
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unlock__Ljava_lang_String_2I
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_unlockall
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unlockall
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_unmap
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unmap__JI
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     io_cat_ai_jni_posix_memman_jni
 * Method:    m_unmap
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_io_cat_ai_jni_posix_1memman_1jni_m_1unmap__Ljava_lang_String_2I
  (JNIEnv *, jobject, jstring, jint);

#ifdef __cplusplus
}
#endif
#endif
