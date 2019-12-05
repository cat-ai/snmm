package io.cat.ai.snmm.core.pointer.struct

import io.cat.ai.snmm.core.pointer.struct.StructTypes.StructMemberType

import scala.math.Ordered.orderingToOrdered

/**
  * Element in a [[io.cat.ai.snmm.core.pointer.struct.AbstractStruct]]
  *
  * It's a collection of different data types which are grouped together and each element in a [[AbstractStruct]] is called member
  * */
final case class StructMember(structMemberType: StructMemberType,
                              structMemberName: String,
                              pos: Int,
                              size: Int) extends Ordered[StructMember] {

  override def compare(that: StructMember): Int =
    this.structMemberName -> this.size compare that.structMemberName -> that.size
}