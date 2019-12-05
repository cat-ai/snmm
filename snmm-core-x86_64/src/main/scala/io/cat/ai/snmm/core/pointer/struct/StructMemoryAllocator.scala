package io.cat.ai.snmm.core.pointer.struct

import io.cat.ai.snmm.core.pointer.Pointer

trait StructMemoryAllocator[M] {

  type size_t = Int

  def allocateMemBlockForStruct(size: size_t): Pointer[Long]

  def deallocateMemBlock(pointer: Pointer[_]): Unit
}
