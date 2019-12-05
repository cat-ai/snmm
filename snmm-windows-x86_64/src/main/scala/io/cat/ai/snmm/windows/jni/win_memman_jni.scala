package io.cat.ai.snmm.windows.jni

class win_memman_jni {

  type Pointer = Long

  @native def map_view_of_file(hFileMappingObject: Pointer,
                               dwDesiredAccess: Int,
                               dwFileOffsetHigh: Int,
                               dwFileOffsetLow: Int,
                               dwNumberOfBytesToMap: Int): Pointer

  @native def map_view_of_file(hFileMappingObject: String,
                               dwDesiredAccess: Int,
                               dwFileOffsetHigh: Int,
                               dwFileOffsetLow: Int,
                               dwNumberOfBytesToMap: Int): Pointer

  @native def virtual_lock(lpAddress: Pointer, dwSize: Int): Boolean

  @native def virtual_protect(lpAddress: Pointer,
                              dwSize: Int,
                              flNewProtect: Int,
                              lpflOldProtect: Pointer): Boolean

  @native def flush_view_of_file(lpBaseAddress: Pointer, dwNumberOfBytesToFlush: Int): Boolean

  @native def virtual_unlock(lpAddress: Pointer, dwSize: Int): Boolean

  @native def unmap_view_of_file(lpBaseAddress: Pointer): Boolean
}