package io.cat.ai.snmm

import io.cat.ai.snmm.common.CTypeAlias._
import io.cat.ai.snmm.core.pointer.{Pointer, PointerFactory}
import io.cat.ai.snmm.posix.jni.SnmmPosixJni
import io.cat.ai.snmm.posix.lib.PosixMman

package object posix {

  object mman extends PosixMman {

    // Lock the pages currently mapped into the address space of the process
    val MCL_CURRENT = 0

    // Lock the pages that become mapped into the address space of the process in the future, when the mappings are established
    val MCL_FUTURE = 0

    /**
      * Lock a range of process address space in physical memory
      *
      * Locks a range of process address space starting at address addr and continuing for length len.
      * The addr must be a multiple of PAGESIZE, which depends on the target platform
      *
      * @param addr - starting address for the range of process address space.
      * @param len  - amount of the memory to lock, in bytes.
      *             There's no limit on the amount of memory that a process may lock, other than the amount of physical memory
      *             in the system.
      **/
    def mlock(addr: *[void], len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_lock(addr.address, len)

    /**
      * Causes all of the pages mapped by the address space of a process to be locked and made memory-resident until unlocked,
      * or the process exits or executes another process. The pages that are locked depend on the flags argument
      *
      * @throws UnsupportedOperationException - you have to be a superuser to lock pages
      *
      * Not available on Mac OS X!
      **/
    def mlockall(flag: Int): Int = throw new UnsupportedOperationException("mlockall unsupported")

    /**
      * Maps a region within the object specified by filedes, beginning at off and continuing for len, into the caller's address space
      * and returns the location
      **/
    def mmap(filedes: *[void],
             len: size_t,
             prot: Int,
             flags: Int,
             fd: Int,
             off_t: Long): *[void] =
      PointerFactory(SnmmPosixJni.POSIX_MMAN.m_map(filedes.address, len, prot, flags, fd, off_t))

    def mmap(filePath: String,
             len: size_t,
             prot: Int,
             flags: Int,
             off_t: Long): *[void] =
      PointerFactory(SnmmPosixJni.POSIX_MMAN.m_map(filePath, len, prot, flags, off_t))

    /**
      * Changes the access protections on any mappings residing in the range starting at addr, and continuing for len bytes
      *
      * @param addr - beginning of the range of addresses whose protection you want to change.
      * @param len  - length of the range of addresses, in bytes.
      * @param prot - new access capabilities for the mapped memory region(s)
      **/
    def mprotect(addr: *[void],
                 len: size_t,
                 prot: Int): *[void] =
      PointerFactory(SnmmPosixJni.POSIX_MMAN.m_protect(addr.address, len, prot))

    /**
      * Writes all modified data to permanent storage locations, if any, in those whole pages containing any part of the address space
      * of the process starting at address addr and continuing for len bytes. The [[msync]] function is used with memory mapped files.
      * If no such storage exists, [[msync]] need not have any effect.
      * If requested, the [[msync]] function then invalidates cached copies of data
      *
      * @param addr - beginning of the range of addresses that you want to synchronize
      * @param len  - length of the range of addresses, in bytes
      * @param prot - bitwise inclusive OR of one or more
      **/
    def msync(addr: *[void], len: size_t, prot: Int): Int =
      SnmmPosixJni.POSIX_MMAN.m_sync(addr.address, len, prot)

    def msync(filePath: String, len: size_t, prot: Int): Int =
      SnmmPosixJni.POSIX_MMAN.m_sync(filePath, len, prot)

    /**
      * Unlocks the specified range of address space, which was locked by a call to [[mlock]] or [[mlockall]]
      * Memory locks don't stack; the memory is unlocked, no matter how many times the same process locked it
      *
      * @param addr - starting address for the range of process address space
      * @param len  - amount of memory to unlock in bytes
      **/
    def munlock(addr: *[void], len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_unlock(addr.address, len)

    def munlock(filePath: String, len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_unlock(filePath, len)

    /**
      * Unlocks all the currently mapped pages of the address space of the calling process.
      * You can lock memory by calling [[mlock]] or [[mlockall]]
      *
      * Any pages that become mapped into the address space of the process after it calls [[munlockall]] aren't locked,
      * unless there's an intervening call to [[mlockall]] specifying MCL_FUTURE or a subsequent call to [[mlockall]] specifying [[MCL_CURRENT]]
      *
      * Calling this function doesn't affect any memory locks set by other processes on the pages
      *
      * Not available on Mac OS X!
      *
      * @param addr - starting address for the range of process address space
      * @param len  - amount of memory to unlock in bytes
      **/
    def munlockall(addr: *[void], len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_unlockall(addr.address, len)

    /**
      * Removes any mappings for pages in the address range starting at addr and continuing for len bytes, rounded up
      * to the next multiple of the page size. Subsequent references to these pages cause a SIGSEGV signal to be set on the process.
      *
      * If there are no mappings in the specified address range, then [[munmap]] has no effect
      *
      * @param addr - beginning of the range of addresses that you want to unmap
      * @param len  - length of the range of addresses in bytes
      **/
    def munmap(addr: *[void], len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_unmap(addr.address, len)

    def munmap(filePath: String, len: size_t): Int =
      SnmmPosixJni.POSIX_MMAN.m_unmap(filePath, len)
  }
}