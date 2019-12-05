#include <windows.h>
#include <fileapi.h>
#include <Winbase.h>
#include <sys/types.h>
#include <iostream>
#include <memoryapi.h>

#include <iostream>
#include <defer.h>

static JNIEnv* globalenv = 0;

JNIEXPORT jlong JNICALL Java_io_cat_ai_windows_jni_c_1jmap_view_of_file(JNIEnv *env,
                                                                        jobject self,
                                                                        jlong filepath,
                                                                        jint dw_desired_access,
                                                                        jint dw_file_offset_high,
                                                                        jint dw_file_offset_low,
                                                                        jint dw_number_of_bytes_to_map) {
    globalenv = env;

    const char *hfilepath = (char*)(*env)->GetStringUTFChars(env, filepath, 0);

    HANDLE h_file = CreateFile(hfilepath,
                              GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE,
                              NULL,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);

    if (h_file == INVALID_HANDLE_VALUE) {
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
        return (jlong)NULL;
    }

    DWORD dw_file_size;

    if (dw_number_of_bytes_to_map == 0) {
        dw_file_size = GetFileSize(h_file, NULL);

        if (dw_file_size == INVALID_FILE_SIZE) {
            CloseHandle(h_file);
            return (jlong)NULL;
        }
    } else {
        dw_file_size = (DWORD)dw_number_of_bytes_to_map;
    }

    const char* ptr_to_mapped_view = (char*)MapViewOfFile(h_mapping,
                                                          dw_desired_access,
                                                          dw_file_offset_high,
                                                          dw_file_offset_low,
                                                          dw_file_size);
    return (jlong)ptr_to_mapped_view;
}