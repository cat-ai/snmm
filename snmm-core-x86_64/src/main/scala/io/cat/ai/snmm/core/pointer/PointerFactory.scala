package io.cat.ai.snmm.core.pointer

object PointerFactory {

  val NULL_PTR = 0L

  def apply(ptr: Long): Pointer[Unit] = ptr match {
    case NULL_PTR => NULL
    case address => RawPointer(address)
  }

  def apply[A](ptr: Pointer[A]): Pointer[Pointer[A]] = ptr match {
    case NULL => create[A](NULL)
    case nativePointer => create[A](nativePointer)
  }

  def create[A](ptr: Long): Pointer[A] = ptr match {
    case NULL_PTR => NULL
    case address => NativePointer[A](address)
  }

  def create[A](ptr: Pointer[A]): Pointer[Pointer[A]] = ptr match {
    case NULL => apply[A](NULL)
    case nativePointer => NativePointer(nativePointer.address)
  }
}