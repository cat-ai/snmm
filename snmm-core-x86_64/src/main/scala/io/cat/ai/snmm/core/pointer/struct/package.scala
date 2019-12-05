package io.cat.ai.snmm.core.pointer

import io.cat.ai.snmm.core.jni.SnmmCore
import io.cat.ai.snmm.core.pointer.struct.StructTypes._
import io.cat.ai.snmm.core.pointer.struct.generic.StructMemberNativeHeapPointer

package object struct {

  def putKeyTypeToStruct(structMemberType: StructMemberType,
                         count: Int,
                         offheapAddress: Long): Unit =
    structMemberType match {
      case JBoolean    => ???
      case JByte       => SnmmCore.SNMM_CORE_JNI.struct_put_byte_key(count, offheapAddress)
      case JChar       => SnmmCore.SNMM_CORE_JNI.struct_put_char_key(count, offheapAddress)
      case JShort      => SnmmCore.SNMM_CORE_JNI.struct_put_short_key(count, offheapAddress)
      case JInt        => SnmmCore.SNMM_CORE_JNI.struct_put_int_key(count, offheapAddress)
      case JFloat      => SnmmCore.SNMM_CORE_JNI.struct_put_float_key(count, offheapAddress)
      case JLong       => SnmmCore.SNMM_CORE_JNI.struct_put_long_key(count, offheapAddress)
      case JDouble     => SnmmCore.SNMM_CORE_JNI.struct_put_double_key(count, offheapAddress)
      case SnmmPointer => SnmmCore.SNMM_CORE_JNI.struct_put_pointer_key(count, offheapAddress)
      case JString     => SnmmCore.SNMM_CORE_JNI.struct_put_string_key(count, offheapAddress)
  }

  def getStructMember[T](pos: Int, structAddr: Long)
                        (implicit structMemberNativeHeapPointer: StructMemberNativeHeapPointer[T]): Pointer[T] =
    structMemberNativeHeapPointer.getMember(pos, structAddr)

  def putStructMember[V](value: V, pos: Int, structAddr: Long)
                        (implicit structMemberNativeHeapPointer: StructMemberNativeHeapPointer[V]): Unit =
    structMemberNativeHeapPointer.putMember(value, pos, structAddr)

  def freeStruct(struct: AbstractStruct with Pointer[Unit]): Unit = SnmmCore.SNMM_CORE_JNI.free(struct.address)

  def alloc(size: Int): Long = SnmmCore.SNMM_CORE_JNI.struct_alloc(size)
}