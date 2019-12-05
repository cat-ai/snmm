package io.cat.ai.snmm.common

import io.cat.ai.snmm.core.pointer.Pointer
import io.cat.ai.snmm.core.pointer.struct.AbstractStruct

object CTypeAlias {

  type *[A] = Pointer[A]
  type **[A] = Pointer[Pointer[A]]
  type ***[A] = Pointer[Pointer[Pointer[A]]]

  type void = Unit

  type bool = Boolean

  type byte = Byte
  type int8_t = Byte

  type char = Char
  type uint16_t = Char
  type short = Short
  type int16_t = Short

  type int = Int
  type int32_t = Int
  type float = Float

  type long = Long
  type int64_t = Long
  type double = Double

  type size_t = Int
  type struct_t = AbstractStruct
  type struct = struct_t with *[void]
}