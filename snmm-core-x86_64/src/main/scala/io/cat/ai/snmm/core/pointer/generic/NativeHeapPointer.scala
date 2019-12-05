package io.cat.ai.snmm.core.pointer.generic

/**
  * Typeclass for typed pointer
  *
  * @see [[io.cat.ai.snmm.core.pointer.Pointer]]
  *
  * Generic pointer is a pointer, which could point to any variables of any types
  * */
trait NativeHeapPointer[T] extends AbstractGenericHeapPointer[T, T]