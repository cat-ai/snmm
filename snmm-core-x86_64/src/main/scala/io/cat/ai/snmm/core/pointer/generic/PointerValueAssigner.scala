package io.cat.ai.snmm.core.pointer.generic


/**
  * In pointer assignment, the pointer is associated with a target (value)
  *
  * @see [[io.cat.ai.snmm.core.pointer.Pointer]]
  *
  * Assigns value of variable someone in memory for the pointer variable to define at
  * */
trait PointerValueAssigner[A] {
  def assign(pointer: Long, idx: Int, value: A): Unit
}