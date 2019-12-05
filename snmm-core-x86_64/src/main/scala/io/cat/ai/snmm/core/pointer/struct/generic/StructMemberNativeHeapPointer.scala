package io.cat.ai.snmm.core.pointer.struct.generic

import io.cat.ai.snmm.core.pointer.Pointer

trait StructMemberNativeHeapPointer[T] {

  def putMember(value: T, pos: Int, structAddr: Long): Unit

  def getMember(pos: Int, structAddr: Long): Pointer[T]
}