package io.cat.ai.snmm.windows.lib

import io.cat.ai.snmm.core.pointer.Pointer

/***
  * @see [["https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/"]]
  */
trait WindowsMemoryApi {

  /**
    * Maps a view of a file mapping into the address space of a calling process
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-mapviewoffile"]]
    **/
  def MapViewOfFile(hFileMappingObject: Pointer[Unit],
                    dwDesiredAccess: Int,
                    dwFileOffsetHigh: Int,
                    dwFileOffsetLow: Int,
                    dwNumberOfBytesToMap: Int = 0): Pointer[Unit]

  /**
    * Locks the specified region of the process's virtual address space into physical memory, ensuring that subsequent access
    * to the region will not incur a page fault
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-virtuallock"]]
    **/
  def VirtualLock(lpAddress: Pointer[Unit],
                  dwSize: Int): Boolean

  /**
    * Changes the protection on a region of committed pages in the virtual address space of the calling process
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-virtualprotect"]]
    **/
  def VirtualProtect(lpAddress: Pointer[Unit],
                     dwSize: Int,
                     flNewProtect: Int,
                     lpflOldProtect: Pointer[Int]): Boolean

  /**
    * Writes to the disk a byte range within a mapped view of a file
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-flushviewoffile"]]
    **/
  def FlushViewOfFile(lpBaseAddress: Pointer[Unit],
                      dwNumberOfBytesToFlush: Int): Boolean

  /**
    * Unlocks a specified range of pages in the virtual address space of a process, enabling the system to swap the pages out
    * to the paging file if necessary
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-virtualunlock"]]
    **/
  def VirtualUnlock(lpAddress: Pointer[Unit],
                    dwSize: Int): Boolean

  /**
    * Unmaps a mapped view of a file from the calling process's address space
    *
    * @see [["https://docs.microsoft.com/en-us/windows/desktop/api/memoryapi/nf-memoryapi-unmapviewoffile"]]
    **/
  def UnmapViewOfFile(lpBaseAddress: Pointer[Unit]): Boolean
}