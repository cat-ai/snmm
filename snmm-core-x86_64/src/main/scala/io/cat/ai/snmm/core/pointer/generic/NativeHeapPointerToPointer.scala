package io.cat.ai.snmm.core.pointer.generic

import io.cat.ai.snmm.core.pointer.Pointer

/**
  * Typeclass for pointer that stores address of pointer
  *
  * @see [[io.cat.ai.snmm.core.pointer.Pointer]]
  *
  * Pointer that points to pointer
  * */
trait NativeHeapPointerToPointer[A] extends AbstractGenericHeapPointer[Pointer[A], Pointer[A]]