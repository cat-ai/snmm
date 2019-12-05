package io.cat.ai.snmm.core.pointer.struct

import io.cat.ai.snmm.core.jni.SnmmCore
import io.cat.ai.snmm.core.pointer.{PointerFactory, Pointer}

package object generic {

  trait StructMemberValueAssignerImplicit {

    implicit def structBooleanMemberPtrValueAssigner: StructMemberValueAssigner[Boolean] =
      (pointer: Long, _: Int, value: Boolean) => SnmmCore.SNMM_CORE_JNI.assign_boolean(pointer, value)

    implicit def structByteMemberPtrValueAssigner: StructMemberValueAssigner[Byte] =
      (pointer: Long, _: Int, value: Byte) => SnmmCore.SNMM_CORE_JNI.assign_byte(pointer, value)

    implicit def structCharMemberPtrValueAssigner: StructMemberValueAssigner[Char] =
      (pointer: Long, _: Int, value: Char) => SnmmCore.SNMM_CORE_JNI.assign_char(pointer, value)

    implicit def structShortMemberPtrValueAssigner: StructMemberValueAssigner[Short] =
      (pointer: Long, _: Int, value: Short) => SnmmCore.SNMM_CORE_JNI.assign_short(pointer, value)

    implicit def structIntMemberPtrValueAssigner: StructMemberValueAssigner[Int] =
      (pointer: Long, _: Int, value: Int) => SnmmCore.SNMM_CORE_JNI.assign_integer(pointer, value)

    implicit def structLongMemberPtrValueAssigner: StructMemberValueAssigner[Long] =
      (pointer: Long, _: Int, value: Long) => SnmmCore.SNMM_CORE_JNI.assign_long(pointer, value)

    implicit def structFloatMemberPtrValueAssigner: StructMemberValueAssigner[Float] =
      (pointer: Long, _: Int, value: Float) => SnmmCore.SNMM_CORE_JNI.assign_float(pointer, value)

    implicit def structDoubleMemberPtrValueAssigner: StructMemberValueAssigner[Double] =
      (pointer: Long, _: Int, value: Double) => SnmmCore.SNMM_CORE_JNI.assign_double(pointer, value)
  }

  trait StructMemberPointerImplicit {

     implicit def structBooleanMemberNativePtr: StructMemberNativeHeapPointer[Boolean] = new StructMemberNativeHeapPointer[Boolean] {

       override def putMember(value: Boolean, pos: Int, structAddr: Long): Unit =
         throw new UnsupportedOperationException("Boolean not supported")

       override def getMember(pos: Int, structAddr: Long): Pointer[Boolean] =
         throw new UnsupportedOperationException("Boolean not supported")
     }

    implicit def structByteMemberNativePtr: StructMemberNativeHeapPointer[Byte] = new StructMemberNativeHeapPointer[Byte] {

      override def putMember(value: Byte, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_byte_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Byte] =
        PointerFactory.create[Byte](SnmmCore.SNMM_CORE_JNI.struct_get_byte_member(pos, structAddr))
    }

    implicit def structCharMemberNativePtr: StructMemberNativeHeapPointer[Char] = new StructMemberNativeHeapPointer[Char] {

      override def putMember(value: Char, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_char_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Char] =
        PointerFactory.create[Char](SnmmCore.SNMM_CORE_JNI.struct_get_char_member(pos, structAddr))
    }

    implicit def structShortMemberNativePtr: StructMemberNativeHeapPointer[Short] = new StructMemberNativeHeapPointer[Short] {

      override def putMember(value: Short, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_short_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Short] =
        PointerFactory.create[Short](SnmmCore.SNMM_CORE_JNI.struct_get_short_member(pos, structAddr))
    }

    implicit def structIntMemberNativePtr: StructMemberNativeHeapPointer[Int] = new StructMemberNativeHeapPointer[Int] {

      override def putMember(value: Int, pos: Int, structAddr: Long): Unit = {
        SnmmCore.SNMM_CORE_JNI.struct_put_int_member(value, pos, structAddr)
      }

      override def getMember(pos: Int, structAddr: Long): Pointer[Int] = {
        PointerFactory.create[Int](SnmmCore.SNMM_CORE_JNI.struct_get_int_member(pos, structAddr))
      }
    }

    implicit def structFloatMemberNativePtr: StructMemberNativeHeapPointer[Float] = new StructMemberNativeHeapPointer[Float] {

      override def putMember(value: Float, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_float_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Float] =
        PointerFactory.create[Float](SnmmCore.SNMM_CORE_JNI.struct_get_float_member(pos, structAddr))
    }

    implicit def structLongMemberNativePtr: StructMemberNativeHeapPointer[Long] = new StructMemberNativeHeapPointer[Long] {

      override def putMember(value: Long, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_long_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Long] =
        PointerFactory.create[Long](SnmmCore.SNMM_CORE_JNI.struct_get_long_member(pos, structAddr))
    }

    implicit def structDoubleMemberNativePtr: StructMemberNativeHeapPointer[Double] = new StructMemberNativeHeapPointer[Double] {

      override def putMember(value: Double, pos: Int, structAddr: Long): Unit =
        SnmmCore.SNMM_CORE_JNI.struct_put_double_member(value, pos, structAddr)

      override def getMember(pos: Int, structAddr: Long): Pointer[Double] =
        PointerFactory.create[Double](SnmmCore.SNMM_CORE_JNI.struct_get_double_member(pos, structAddr))
    }
  }
}