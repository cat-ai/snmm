package io.cat.ai.snmm.core.pointer.struct.generic

import io.cat.ai.snmm.core.pointer.generic.PointerValueAssigner

trait StructMemberValueAssigner[A] extends PointerValueAssigner[A] {
  override def assign(pointer: Long, idx: Int = 0, value: A): Unit
}