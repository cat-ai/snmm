package io.cat.ai.snmm.core.pointer

import io.cat.ai.snmm.core.jni.SnmmCore

/**
  * Pointer to a memory address
  *
  * Base trait for all off-heap objects
  *
  * Provides C-style paradigm to access memory underlying the native pointer
  *
  * Pointers to native memory are eligible for Garbage Collection, but the off-heap data referred to is not
  */
trait Pointer[+A] extends AutoCloseable {

  /**
    * @return memory address
    */
  def address: Long
}

/**
  * A pointer that has no associated data type with it
  * Can hold address of any type and can be typecasted to any type
  *
  * Represents void* pointer
  *
  * [[io.cat.ai.snmm.core.pointer.generic.NativeHeapDynamicMemoryAllocator.allocateMemBlock]] and
  * [[io.cat.ai.snmm.core.pointer.generic.NativeHeapDynamicMemoryAllocator.allocateMemBlockWithInit]]
  *
  * allows these functions to be used to allocate memory of any data type (just because of void*)
  * */
final case class RawPointer(override val address: Long) extends Pointer[Unit] {
  override def close: Unit = SnmmCore.SNMM_CORE_JNI.free(address)
}

/**
  * A generic pointer is a variable whose value is the address of another variable, i.e., direct address of the memory location.
  *
  * Like any variable or constant, you must declare a pointer before using it to store any variable address.
  * */
final case class NativePointer[A](override val address: Long) extends Pointer[A] {
  override def close: Unit = SnmmCore.SNMM_CORE_JNI.free(address)
}

/**
  * NULL is defined as an implementation-defined null pointer constant, which can be portably expressed as the integer value 0
  * */
case object NULL extends Pointer[Nothing] {

  override def address: Long = throw new NullPointerException("NULL [0]")

  override def close: Unit = ()
}