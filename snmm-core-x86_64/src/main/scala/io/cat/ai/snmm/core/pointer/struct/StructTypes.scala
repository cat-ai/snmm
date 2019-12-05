package io.cat.ai.snmm.core.pointer.struct

object StructTypes {

  sealed trait StructMemberType

  /**
    * aka Boolean
    *
    * Boolean is a 1-bit datatype. ByteBuffer works with bytes.
    * You'll have to decide yourself how you'll represent a boolean as a byte
    * (such as 0 for false and 1 for true, or 0 for false and non-zero for true).
    *
    * [[Boolean]]
    * */
  case object JBoolean extends StructMemberType

  sealed abstract class AbstractNumericStructMemberType extends StructMemberType

  sealed abstract class AbstractIntegralStructMemberType extends AbstractNumericStructMemberType

  /**
    * aka Byte
    *
    * int_8t
    *
    * [[Byte]]
    * */
  case object JByte extends AbstractIntegralStructMemberType

  /**
    * aka Char
    *
    * uint_16t
    *
    * [[Char]]
    * */
  case object JChar extends AbstractIntegralStructMemberType

  /**
    * aka Short
    *
    * int_16t
    *
    * [[Short]]
    * */
  case object JShort extends AbstractIntegralStructMemberType

  /**
    * aka Int
    *
    * int_32t
    *
    * [[Int]]
    * */
  case object JInt extends AbstractIntegralStructMemberType

  /**
    * aka Long
    *
    * int_64t
    *
    * [[Long]]
    * */
  case object JLong extends AbstractIntegralStructMemberType

  sealed abstract class AbstractFloatingPointStructMemberType extends AbstractNumericStructMemberType

  /**
    * aka Float (32-bit IEEE 754)
    *
    * 32 bits, with 1 sign bit, 8 bits of exponent, and 23 bits of the significand
    *
    * [[Float]]
    * */
  case object JFloat extends AbstractFloatingPointStructMemberType

  /**
    * aka Double (64-bit IEEE 754)
    *
    * 64 bits, with 1 sign bit, 11 bits of exponent, and 52 bits of significand
    *
    * [[Double]]
    * */
  case object JDouble extends AbstractFloatingPointStructMemberType

  /**
    * aka Pointer
    * [[io.cat.ai.snmm.core.pointer.Pointer]]
    * */
  case object SnmmPointer extends StructMemberType

  /**
    * aka String
    *
    * Modified UTF-8 strings are the same as those used by the Java VM.
    *
    * Modified UTF-8 strings are encoded so that character sequences that contain only non-null ASCII characters can be represented
    * using only one byte per character, but all Unicode characters can be represented
    * */
  case object JString extends StructMemberType

}
