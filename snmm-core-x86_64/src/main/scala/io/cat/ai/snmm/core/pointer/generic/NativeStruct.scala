package io.cat.ai.snmm.core.pointer.generic

import io.cat.ai.snmm.core.pointer.Pointer

trait NativeStruct extends Pointer[Nothing] {

  def structMemberTable: Map[Int, Long]

  def free: Unit
}