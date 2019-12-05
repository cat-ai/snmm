package io.cat.ai.snmm.core.pointer.generic

import io.cat.ai.snmm.core.pointer.Pointer

/**
  * Base interface for all pointers
  *
  *  @see [[io.cat.ai.snmm.core.pointer.Pointer]]
  * */
abstract class AbstractGenericHeapPointer[A, B] {

  /**
    * @return value referenced by this pointer
    */
  def deref(ptr: Pointer[B]): A

  /**
    * @return memory address pointed to
    */
  def addressOf(value: A): Pointer[B]
}