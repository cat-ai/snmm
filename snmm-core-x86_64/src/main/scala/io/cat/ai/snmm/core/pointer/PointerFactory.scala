package io.cat.ai.snmm.core.pointer

import io.cat.ai.snmm.core.pointer.generic.NativeStruct

object PointerFactory {

  object vals {
    val NULL = 0L
  }

  def apply(ptr: Long): Pointer[Unit] = ptr match {
    case _ @ vals.NULL => NULL
    case address => RawPointer(address)
  }

  def apply[A](ptr: Pointer[A]): Pointer[Pointer[A]] = ptr match {
    case NULL => create[A](NULL)
    case nativePointer => create[A](nativePointer)
  }

  def create[A](ptr: Long): Pointer[A] = ptr match {
    case _ @ vals.NULL => NULL
    case address => NativePointer[A](address)
  }

  def create[A](ptr: Pointer[A]): Pointer[Pointer[A]] = ptr match {
    case NULL => apply[A](NULL)
    case nativePointer => NativePointer(nativePointer.address)
  }

  def createStruct[A](ptr: Long): NativeStruct = ptr match {
    case _ @ vals.NULL => throw new NullPointerException("NULL [0]")
    case address => ???
  }
}