package io.cat.ai.snmm

import io.cat.ai.snmm.core.pointer.{Pointer, PointerFactory}
import io.cat.ai.snmm.windows.jni.SnmmWindowsJni
import io.cat.ai.snmm.windows.lib.WindowsMemoryApi

package object windows {

  object memoryapi extends WindowsMemoryApi {

    /**
      * Maps a view of a file mapping into the address space of a calling process
      * */
    def MapViewOfFile(hFileMappingObject: Pointer[Unit],
                      dwDesiredAccess: Int,
                      dwFileOffsetHigh: Int,
                      dwFileOffsetLow: Int,
                      dwNumberOfBytesToMap: Int = 0): Pointer[Unit] =
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
    def VirtualLock(lpAddress: Pointer[Unit],
                    dwSize: Int): Boolean =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_lock(lpAddress.address, dwSize)

    /**
      * Changes the protection on a region of committed pages in the virtual address space of the calling process
      * */
    def VirtualProtect(lpAddress: Pointer[Unit],
                       dwSize: Int,
                       flNewProtect: Int,
                       lpflOldProtect: Pointer[Int]): Boolean =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_protect(lpAddress.address, dwSize, flNewProtect, lpflOldProtect.address)

    /**
      * Writes to the disk a byte range within a mapped view of a file
      * */
    def FlushViewOfFile(lpBaseAddress: Pointer[Unit],
                        dwNumberOfBytesToFlush: Int): Boolean =
      SnmmWindowsJni.WINDOWS_MEMORY_API.flush_view_of_file(lpBaseAddress.address, dwNumberOfBytesToFlush)


    /**
      * Unlocks a specified range of pages in the virtual address space of a process, enabling the system to swap the pages out
      * to the paging file if necessary
      * */
    def VirtualUnlock(lpAddress: Pointer[Unit], dwSize: Int): Boolean =
      SnmmWindowsJni.WINDOWS_MEMORY_API.virtual_unlock(lpAddress.address, dwSize)

    /**
      * Unmaps a mapped view of a file from the calling process's address space
      * */
    def UnmapViewOfFile(lpBaseAddress: Pointer[Unit]): Boolean =
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
