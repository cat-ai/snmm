package io.cat.ai.snmm.core.pointer.struct


/**
  * Composite data type (or record) declaration that defines a physically grouped list of variables under one name in a block of memory,
  * allowing the different variables to be accessed via a single pointer or by the struct declared name which returns the same address
  *
  * Subclasses of AbstractStruct instantiated via macro annotation
  *
  * @see [[io.cat.ai.snmm.macros.struct.SnmmStructMacro.struct]]
  * @see [[io.cat.ai.snmm.macros.struct.SnmmStructMacro.offheap_alloc]]
  *
  * @example {{{
  *
  *         @struct @offheap_alloc
  *         case class OffheapStruct(intField1: Int = 232323,
  *                                  intField2: Int = 9999999,
  *                                  floatField1: Float = 3.14f,
  *                                  longField1: Long = 7654321L)
  *
  *         import OffheapStruct._
  *
  *         val offheapStruct = OffheapStruct()
  *
  *         val intFromStruct1: Int = offheapStruct*->intField1  //returns 232323
  *         val intFromStruct2: Int = offheapStruct*->intField2  //returns 9999999
  *         val floatFromStruct: Float = offheapStruct*->floatField1  //returns 3333
  *         val longFromStruct4: Long = offheapStruct*->longField1  //returns 7654321
  *
  *         free(offheapSnmmStruct)
  *
  *      }}}
  * */
abstract class AbstractStruct {

  /**
    * A struct is a type consisting of a sequence of members whose storage is allocated in an ordered sequence
    * @see [[io.cat.ai.snmm.core.pointer.struct.StructMember]]
    * */
  def structMembers: Seq[StructMember]
}