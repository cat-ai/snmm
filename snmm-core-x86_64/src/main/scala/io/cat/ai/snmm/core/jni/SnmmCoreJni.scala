package io.cat.ai.snmm.core.jni

import io.cat.ai.snmm.common.Common.Pointer

class SnmmCoreJni {

  /***
    * C syntax: dereference, address, size, assign
    */
  @native def integer_pointer(value: Int): Pointer

  @native def boolean_pointer(value: Boolean): Pointer

  @native def byte_pointer(value: Byte): Pointer

  @native def char_pointer(value: Char): Pointer

  @native def short_pointer(value: Short): Pointer

  @native def float_pointer(value: Float): Pointer

  @native def long_pointer(value: Long): Pointer

  @native def double_pointer(value: Double): Pointer

  @native def string_pointer(value: String): Pointer

  @native def assign_byte(ptr: Pointer, value: Byte): Unit

  @native def assign_boolean(ptr: Pointer, value: Boolean): Unit

  @native def assign_char(ptr: Pointer, value: Char): Unit

  @native def assign_short(ptr: Pointer, value: Short): Unit

  @native def assign_integer(ptr: Pointer, value: Int): Unit

  @native def assign_float(ptr: Pointer, value: Float): Unit

  @native def assign_long(ptr: Pointer, value: Pointer): Unit

  @native def assign_double(ptr: Pointer, value: Double): Unit

  @native def deref_boolean(ptr: Pointer): Boolean

  @native def deref_byte(ptr: Pointer): Byte

  @native def deref_short(ptr: Pointer): Short

  @native def deref_char(ptr: Pointer): Char

  @native def deref_int(ptr: Pointer): Int

  @native def deref_float(ptr: Pointer): Float

  @native def deref_long(ptr: Pointer): Pointer

  @native def deref_double(ptr: Pointer): Double

  @native def deref_string(ptr: Pointer): String

  @native def boolean_size: Int

  @native def char_size: Int

  @native def short_size: Int

  @native def int_size: Int

  @native def byte_size: Int

  @native def long_size: Int

  @native def float_size: Int

  @native def double_size: Int

  @native def string_size: Int

  @native def byte_pointer_size: Int

  @native def char_pointer_size: Int

  @native def short_pointer_size: Int

  @native def integer_pointer_size: Int

  @native def float_pointer_size: Int

  @native def long_pointer_size: Int

  @native def double_pointer_size: Int

  @native def string_pointer_size: Int

  /***
    * stdlib
    */
  @native def malloc(size: Int): Pointer

  @native def malloc_struct(size: Int): Pointer

  @native def calloc(n: Int, size: Int): Pointer

  @native def realloc(ptr: Pointer, size: Int): Pointer

  @native def free(nBytes: Pointer): Unit

  /***
    * string
    */
  @native def mem_cpy(str1: Pointer, str2: Pointer, n: Int): Pointer

  @native def mem_move(str1: Pointer, str2: Pointer, n: Int): Pointer

  @native def mem_chr(str1: Pointer, c: Int, n: Int): Pointer

  @native def mem_cmp(str1: Pointer, str2: Pointer, n: Int): Int

  @native def mem_set(str: Pointer, c: Int, n: Int): Pointer

  @native def str_cat(dest: Pointer, src: Pointer): Pointer

  @native def strn_cat(dest: Pointer, src: Pointer, n: Int): Pointer

  @native def str_chr(str: Pointer, c: Int): Pointer

  @native def strr_chr(str: Pointer, c: Int): Pointer

  @native def str_cmp(str1: Pointer, str2: Pointer): Int

  @native def strn_cmp(str1: Pointer, str2: Pointer, n: Int): Int

  @native def str_coll(str1: Pointer, str2: Pointer): Int

  @native def str_cpy(dest: Pointer, src: Pointer): Pointer

  @native def str_len(s: Pointer): Int

  @native def str_spn(s: Pointer, reject: Pointer): Int

  @native def str_cspn(s: Pointer, reject: Pointer): Int

  @native def str_pbrk(s: Pointer, reject: Pointer): Pointer

  @native def str_str(s: Pointer, reject: Pointer): Pointer

  @native def str_tok(s: Pointer, reject: Pointer): Pointer

  @native def str_xfrm(s: Pointer, reject: Pointer, n: Int): Int

  /***
    * structs, struct member, struct key
    */
  @native def struct_alloc(size: Int): Pointer

  @native def struct_free(address: Pointer): Unit


  @native def struct_put_byte_key(count: Int, address: Pointer): Unit

  @native def struct_put_char_key(count: Int, address: Pointer): Unit

  @native def struct_put_short_key(count: Int, address: Pointer): Unit

  @native def struct_put_int_key(count: Int, address: Pointer): Unit

  @native def struct_put_float_key(count: Int, address: Pointer): Unit

  @native def struct_put_long_key(count: Int, address: Pointer): Unit

  @native def struct_put_double_key(count: Int, address: Pointer): Unit

  @native def struct_put_string_key(count: Int, address: Pointer): Unit

  @native def struct_put_pointer_key(count: Int, address: Pointer): Unit


  @native def struct_get_boolean_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_byte_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_char_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_short_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_int_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_long_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_float_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_double_member(pos: Int, address: Pointer): Pointer

  @native def struct_get_string_member(pos: Int, address: Pointer): Pointer


  @native def struct_put_boolean_member(value: Boolean, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_byte_member(value: Byte, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_and_get_int_member(value: Int, pos: Int, structAddr: Pointer): Pointer

  @native def struct_put_char_member(value: Char, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_short_member(value: Short, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_int_member(value: Int, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_long_member(value: Long, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_float_member(value: Float, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_double_member(value: Double, pos: Int, structAddr: Pointer): Unit

  @native def struct_put_string_member(value: String, pos: Int, structAddr: Pointer): Unit
}