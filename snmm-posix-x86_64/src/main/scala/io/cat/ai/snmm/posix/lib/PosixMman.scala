package io.cat.ai.snmm.posix.lib

import io.cat.ai.snmm.core.pointer.Pointer

trait PosixMman {

  /**
    * Locks pages in the address range starting at addr and continuing for len bytes.  All pages that contain a part of the
    * specified address range are guaranteed to be resident in RAM when the call returns successfully; the pages are guaranteed
    * to stay in RAM until later unlocked
    *
    * @see [["http://man7.org/linux/man-pages/man2/mlock.2.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/mlock.2.html"]]
    * */
  def mlock(addr: Pointer[Unit], len: Int): Int

  /**
    * Locks all pages mapped into the address space of the calling process. This includes the pages of the code, data and stack
    * segment, as well as shared libraries, user space kernel data, shared memory, and memory-mapped files.  All mapped pages are
    * guaranteed to be resident in RAM when the call returns successfully; the pages are guaranteed to stay in RAM until later unlocked
    *
    * @see [["http://man7.org/linux/man-pages/man2/mlock.2.html"]]
    * */
  def mlockall(flag: Int): Int

  /**
    * Creates a new mapping in the virtual address space of the calling process. The starting address for the new mapping is
    * specified in addr. The length argument specifies the length of the mapping (which must be greater than 0)
    *
    * @see [["http://man7.org/linux/man-pages/man2/mmap.2.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/mmap.2.html"]]
    * */
  def mmap(filedes: Pointer[Unit], len: Int, prot: Int, flags: Int, fd: Int, off_t: Long): Pointer[Unit]

  def mmap(filepath: String, len: Int, prot: Int, flags: Int, off_t: Long): Pointer[Unit]

  /**
    * Changes the access protections for the calling process's memory pages containing any part of the address range in the interval
    * [addr, addr+len-1].  addr must be aligned to a page boundary
    *
    * @see [["http://man7.org/linux/man-pages/man2/mprotect.2.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/mprotect.2.html"]]
    * */
  def mprotect(addr: Pointer[Unit], len: Int, prot: Int): Pointer[Unit]

  /**
    * Flushes changes made to the in-core copy of a file that was mapped into memory using [[mmap]] back to the filesystem.
    * Without use of this call, there is no guarantee that changes are written back before [[munmap]] is called.
    * To be more precise, the part of the file that corresponds to the memory area starting at addr and having
    * length length is updated
    *
    * @see [["http://man7.org/linux/man-pages/man2/msync.2.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/msync.2.html"]]
    * */
  def msync(addr: Pointer[Unit], len: Int, prot: Int): Int

  def msync(filePath: String, len: Int, prot: Int): Int

  /**
    * Perform the converse operation, unlocking part or all of the calling process's virtual address space, so that
    * pages in the specified virtual address range may once more to be swapped out if required by the kernel memory manager
    *
    * @see [["http://man7.org/linux/man-pages/man2/mlock.2.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/mlock.2.html"]]
    * */
  def munlock(addr: Pointer[Unit], len: Int): Int

  def munlock(filePath: String, len: Int): Int

  /**
    * Perform the converse operation, unlocking part or all of the calling process's virtual address space, so that
    * pages in the specified virtual address range may once more to be swapped out if required by the kernel memory manager
    *
    * @see [["http://man7.org/linux/man-pages/man2/mlock.2.html"]]
    * */
  def munlockall(addr: Pointer[Unit], len: Int): Int

  /**
    * Function shall remove any mappings for those entire pages containing any part of the address space of the process
    * starting at addr and continuing for len bytes. Further references to these pages shall result in the generation of a
    * SIGSEGV signal to the process.  If there are no mappings in the specified address range, then [[munmap]] has no effect
    *
    * @see [["http://man7.org/linux/man-pages/man3/munmap.3p.html"]]
    *
    * @see [["https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/munmap.2.html"]]
    * */
  def munmap(addr: Pointer[Unit], len: Int): Int

  def munmap(filePath: String, len: Int): Int
}
