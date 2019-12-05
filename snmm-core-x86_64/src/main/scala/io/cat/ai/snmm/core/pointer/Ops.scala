package io.cat.ai.snmm.core.pointer

import io.cat.ai.snmm.core.pointer.exceptions.PointerArithmeticException
import io.cat.ai.snmm.core.pointer.generic.{NativeSize, PointerValueAssigner}

object Ops {

  trait PointerOps {

    private val ptrArithmeticExc = new PointerArithmeticException("NULL can't perform pointer arithmetic")

    implicit class PointerArithmetic[A](ptr: Pointer[A]) { self =>

      def +(n: Int)(implicit nSize: NativeSize[A]): Pointer[A] = self.ptr match {
        case NULL => throw ptrArithmeticExc
        case ptrA => PointerFactory.create[A](ptrA.address + n * nSize.size)
      }

      def -(n: Int)(implicit nSize: NativeSize[A]): Pointer[A] = ptr match {
        case NULL => throw ptrArithmeticExc
        case ptrA => PointerFactory.create[A](ptrA.address - n * nSize.size)
      }
    }

    implicit class PointerUpdater[A](val ptr: Pointer[A]) {
      def update(n: Int, value: A)
                (implicit valueAssigner: PointerValueAssigner[A]): Unit = valueAssigner.assign(ptr.address, n, value)
    }

    implicit class PointerToPointerUpdater[A](val ptr: Pointer[Pointer[A]]) {
      def update(n: Int, value: Pointer[A])
                (implicit valueAssigner: PointerValueAssigner[Pointer[A]]): Unit = valueAssigner.assign(ptr.address, n, value)
    }

    implicit class PointerEq[A](ptr: Pointer[A]) {

      def ===[B](that: Pointer[B]): Boolean = this.ptr -> that match {

        case (NULL, NULL) | (NULL, _) | (_, NULL) => false

        case (ptrA, ptrB) => ptrA.address == ptrB.address
      }

      def =!=[B](that: Pointer[B]): Boolean = ! ===(that)
    }
  }
}
