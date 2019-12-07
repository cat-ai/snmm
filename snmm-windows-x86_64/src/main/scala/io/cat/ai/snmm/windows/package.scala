package io.cat.ai.snmm

import io.cat.ai.snmm.core.pointer.{Pointer, PointerFactory}
import io.cat.ai.snmm.windows.jni.SnmmWindowsJni
import io.cat.ai.snmm.windows.lib.WindowsMemoryApi

package object windows {

  import syntax._

  object memoryapi extends WindowsMemoryApi {

    /**
      * Maps a view of a file mapping into the address space of a calling process
      * */
    def MapViewOfFile(hFileMappingObject: HANDLE,
                      dwDesiredAccess: DWORD,
                      dwFileOffsetHigh: DWORD,
                      dwFileOffsetLow: DWORD,
                      dwNumberOfBytesToMap: SIZE_T = 0): LPVOID =
      PointerFactory {
        SnmmWindowsJni
          .WINDOWS_MEMORY_API
          .map_view_of_file(
            hFileMappingObject.address,
            dwDesiredAccess,
            dwFileOffsetHigh,
            dwFileOffsetLow,
            dwNumberOfBytesToMap
          )
      }

    /**
      * Locks the specified region of the process's virtual address space into physical memory, ensuring that subsequent access
      * to the region will not incur a page fault.
      * */
    def VirtualLock(lpAddress: LPVOID,
                    dwSize: SIZE_T): BOOL =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_lock(lpAddress.address, dwSize)

    /**
      * Changes the protection on a region of committed pages in the virtual address space of the calling process
      * */
    def VirtualProtect(lpAddress: LPVOID,
                       dwSize: SIZE_T,
                       flNewProtect: DWORD,
                       lpflOldProtect: PDWORD): BOOL =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_protect(lpAddress.address, dwSize, flNewProtect, lpflOldProtect.address)

    /**
      * Writes to the disk a byte range within a mapped view of a file
      * */
    def FlushViewOfFile(lpBaseAddress: LPCVOID,
                        dwNumberOfBytesToFlush: SIZE_T): BOOL =
      SnmmWindowsJni.WINDOWS_MEMORY_API.flush_view_of_file(lpBaseAddress.address, dwNumberOfBytesToFlush)


    /**
      * Unlocks a specified range of pages in the virtual address space of a process, enabling the system to swap the pages out
      * to the paging file if necessary
      * */
    def VirtualUnlock(lpAddress: LPVOID, dwSize: SIZE_T): BOOL =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_unlock(lpAddress.address, dwSize)

    /**
      * Unmaps a mapped view of a file from the calling process's address space
      * */
    def UnmapViewOfFile(lpBaseAddress: LPCVOID): BOOL =
      SnmmWindowsJni.WINDOWS_MEMORY_API.unmap_view_of_file(lpBaseAddress.address)
  }

  object syntax {
    type BYTE = Char
    type TCHAR = BYTE
    type shortWORD = Short
    type WCHAR = TCHAR
    type DWORD = Int
    type BOOL = Boolean
    type LONGLONG = Long
    type void = Unit
    type LPVOID = Pointer[Unit]
    type HANDLE = LPVOID
    type LPXXX = LPVOID
    type SIZE_T = DWORD
    type PDWORD = Pointer[DWORD]
    type LPCTSTR = Pointer[Char]
    type LPCVOID = LPVOID
  }
}
