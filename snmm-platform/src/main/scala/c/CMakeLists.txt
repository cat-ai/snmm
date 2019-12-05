cmake_minimum_required(VERSION 3.14)

project(c C)

set(CMAKE_C_STANDARD 99)

add_executable(c src/c_jni.c src/c_jni.h src/utils/struct_jni_byte_buf.c src/utils/struct_jni_byte_buf.h)