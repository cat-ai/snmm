package io.cat.ai.snmm.core.pointer.generic

import io.cat.ai.snmm.core.pointer.Pointer

/**
  * Typeclass for assigning a value to typed pointer
  *
  * @see [[io.cat.ai.snmm.core.pointer.Pointer]]
  * */
trait PointerToPointerValueAssigner[A] extends PointerValueAssigner[Pointer[A]]