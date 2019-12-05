#include <windows.h>
#include <iostream>
#include <sys/types.h>
#include <fileapi.h>
#include <Winbase.h>
#include <memoryapi.h>

#include <defer.h>

static JNIEnv* globalenv = 0;

JNIEXPORT jlong JNICALL Java_io_cat_ai_windows_jni_c_1jmap_view_of_file(JNIEnv *env,
                                                                        jobject self,
                                                                        jstring hFileMappingObject,
                                                                        jint dwDesiredAccess,
                                                                        jint dwFileOffsetHigh,
                                                                        jint dwFileOffsetLow,
                                                                        jint dwNumberOfBytesToMap) {
    globalenv = env;
    const char *hfilepath = (char*)(*env)->GetStringUTFChars(env, hFileMappingObject, 0);
    HANDLE h_file = CreateFile(hfilepath,
                               GENERIC_READ | GENERIC_WRITE,
                               FILE_SHARE_READ | FILE_SHARE_WRITE,
                               NULL,
                               CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);

    if (h_file == INVALID_HANDLE_VALUE) {
        (*env)->ReleaseStringUTFChars(env, hfilepath, hFileMappingObject);
        return (jlong)NULL;
    }

    HANDLE h_mapping = CreateFileMapping(h_file,
                                         NULL,
                                         PAGE_READONLY,
                                         0,
                                         0,
                                         NULL);

    if (h_mapping == NULL) {
        CloseHandle(h_file);
        (*env)->ReleaseStringUTFChars(env, hfilepath, hFileMappingObject);

        return (jlong)NULL;
    }

    DWORD dw_file_size;
    if (dwNumberOfBytesToMap == 0) {
        dw_file_size = GetFileSize(h_file, NULL);

        if (dw_file_size == INVALID_FILE_SIZE) {
            (*env)->ReleaseStringUTFChars(env, hfilepath, hFileMappingObject);
            CloseHandle(h_file);
            return (jlong)NULL;
        }
    } else {
        dw_file_size = (DWORD)dw_number_of_bytes_to_map;
    }

    void *ptr_to_mapped_view = (void*)MapViewOfFile(h_mapping,
                                                    dwDesiredAccess,
                                                    dwFileOffsetHigh,
                                                    dwFileOffsetLow,
                                                    dw_file_size);
    if (ptr_to_mapped_view == NULL) {
        CloseHandle(h_mapping);
        CloseHandle(h_file);
        (*env)->ReleaseStringUTFChars(env, hfilepath, hFileMappingObject);
        return (jlong)NULL;
    }

    (*env)->ReleaseStringUTFChars(env, hfilepath, hFileMappingObject);
    return (jlong)ptr_to_mapped_view;
}

JNIEXPORT jlong JNICALL Java_io_cat_ai_windows_jni_c_2jmap_view_of_file(JNIEnv *env,
                                                                        jobject self,
                                                                        jlong hFileMappingObject,
                                                                        dwDesiredAccess,
                                                                        dwFileOffsetHigh,
                                                                        dwFileOffsetLow,
                                                                        dwNumberOfBytesToMap) {
    globalenv = env;

    HANDLE h_file = (HANDLE)hFileMappingObject;
    HANDLE h_mapping = CreateFileMapping(h_file,
                                         NULL,
                                         PAGE_READONLY,
                                         0,
                                         0,
                                         NULL);

    if (h_mapping == NULL) {
        CloseHandle(h_file);
        return (jlong)NULL;
    }

    DWORD dw_file_size;
    if (dwNumberOfBytesToMap == 0) {
        dw_file_size = GetFileSize(h_file, NULL);

        if (dw_file_size == INVALID_FILE_SIZE) {
            CloseHandle(h_file);
            return (jlong)NULL;
        }
    } else {
        dw_file_size = (DWORD)dw_number_of_bytes_to_map;
    }

    void* ptr_to_mapped_view = (char*)MapViewOfFile(h_mapping,
                                                    dwDesiredAccess,
                                                    dwFileOffsetHigh,
                                                    dwFileOffsetLow,
                                                    dw_file_size);
    if (ptr_to_mapped_view == NULL) {
        CloseHandle(h_mapping);
        CloseHandle(h_file);
        return (jlong)NULL;
    }

    return (jlong)ptr_to_mapped_view;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_windows_jni_c_1junmap_view_of_file(JNIEnv *env,
                                                                             jobject self,
                                                                             jlong lpAddress) {
    globalenv = env;
    LPCVOID ptr_to_mapped_view = (LPCVOID)lpAddress;
    BOOL is_unmapped = UnmapViewOfFile(ptr_to_mapped_view);

    return (jboolean)is_unmapped;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_windows_jni_c_1jvirtual_lock(JNIEnv *env,
                                                                       jobject self,
                                                                       jlong lpAddress,
                                                                       jint dw_size) {
    globalenv = env;
    LPCVOID virt_mem = (LPCVOID)lpAddress;
    BOOL is_locked = VirtualLock(ptr_to_mapped_view);

    return (jboolean)is_locked;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_windows_jni_c_1jvirtual_unlock(JNIEnv *env,
                                                                         jobject self,
                                                                         jlong lpAddress,
                                                                         jint dw_size) {
    globalenv = env;
    LPCVOID ptr_to_mapped_view = (LPCVOID)lpAddress;
    BOOL is_unlocked = VirtualUnlock(ptr_to_mapped_view);

    return (jboolean)is_unlocked;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_windows_jni_c_1jvirtual_protect(JNIEnv *env,
                                                                          jobject self,
                                                                          jlong lpAddress,
                                                                          jint dwSize,
                                                                          jint flNewProtect,
                                                                          jlong lpflOldProtect,
                                                                          jint dw_size) {
    globalenv = env;
    LPCVOID lp_address = (LPCVOID)lpAddress;
    SIZE_T dw_size = (SIZE_T)dwSize;
    DWORD fl_new_protect = (DWORD)flNewProtect;
    PDWORD lp_fl_old_protect = (PDWORD)lpflOldProtect;
    BOOL is_protected = VirtualProtect(lp_address, dw_size, fl_new_protect, lp_fl_old_protect);

    return (jboolean)is_protected;
}

JNIEXPORT jboolean JNICALL Java_io_cat_ai_windows_jni_c_1jflush_view_of_file(JNIEnv *env,
                                                                             jobject self,
                                                                             jlong lpBaseAddress,
                                                                             jint dwNumberOfBytesToFlush) {
    globalenv = env;
    LPCVOID lp_address = (LPCVOID)lpBaseAddress;
    SIZE_T dw_number_of_bytes_to_flush = (SIZE_T)dwNumberOfBytesToFlush;
    BOOL is_flushed = FlushViewOfFile(lp_address, dw_number_of_bytes_to_flush);

    return (jboolean)is_flushed;
}