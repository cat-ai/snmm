package io.cat.ai.snmm.posix.jni

class SnmmPosixMman {

  type Pointer = Long

  @native def m_lock(addr: Pointer, len: Int): Int

  @native def m_lockall(n: Int): Int = throw new UnsupportedOperationException("Not supported")

  @native def m_map(filedes: Pointer, len: Int, prot: Int, flags: Int, fd: Int, off_t: Long): Pointer

  @native def m_map(filePath: String, len: Int, prot: Int, flags: Int, off_t: Long): Pointer

  @native def m_protect(addr: Pointer, len: Int, prot: Int): Pointer

  @native def m_sync(addr: Pointer, len: Int, prot: Int): Int

  @native def m_sync(filePath: String, len: Int, prot: Int): Int

  @native def m_unlock(addr: Pointer, len: Int): Int

  @native def m_unlock(filePath: String, len: Int): Int

  @native def m_unlockall(addr: Pointer, len: Int): Int

  @native def m_unmap(addr: Pointer, len: Int): Int

  @native def m_unmap(filePath: String, len: Int): Int
}