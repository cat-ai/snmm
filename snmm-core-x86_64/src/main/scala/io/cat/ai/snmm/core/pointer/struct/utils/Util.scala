package io.cat.ai.snmm.core.pointer.struct.utils

import io.cat.ai.snmm.core.pointer.struct.StructMember
import io.cat.ai.snmm.core.pointer.struct.StructTypes._

object Util {

  def assignPositionToMembers(membersSeq: Seq[StructMember]): Seq[StructMember] =
    membersSeq
      .sorted
      .foldLeft(Seq.empty[StructMember]) {
        (xs, nextMember) => xs match {
          case x +: _ if x.structMemberType == nextMember.structMemberType => nextMember.copy(pos = x.pos + 1) +: xs
          case _ => nextMember +: xs
        }
      }
      .reverse

  def parseTypeAsStringToStructMember(typeAsString: String): StructMemberType = typeAsString match {
    case "Boolean" | "bool"               => JBoolean
    case "Byte"    | "int8_t"   | "byte"  => JByte

    case "Char"    | "uint16_t" | "char"  => JChar
    case "Short"   | "int16_t"  | "short" => JShort

    case "Int"     | "int32_t"  | "int"   => JInt
    case "Float"   | "float"              => JFloat

    case "Double"  | "double"             => JDouble
    case "Long"    | "int64_t"  | "long"  => JLong

    case "String"                         => JString
  }

  def parseStructMemberTypeToStringSeq(structMemberType: StructMemberType): Seq[String] = {

    def matchNumericType(numericType: AbstractNumericStructMemberType): Seq[String] = {

      def matchIntegralType(integralType: AbstractIntegralStructMemberType): Seq[String] = integralType match {
        case JByte   => "byte"  :: "int8_t"   :: "Byte"  :: Nil
        case JChar   => "char"  :: "uint16_t" :: "Char"  :: Nil
        case JShort  => "short" :: "int16_t"  :: "Short" :: Nil
        case JInt    => "int"   :: "int32_t"  :: "Int"   :: Nil
        case JLong   => "long"  :: "int64_t"  :: "Long"  :: Nil
      }

      def matchFloatingPointType(floatingPointType: AbstractFloatingPointStructMemberType): Seq[String] = floatingPointType match {
        case JFloat  => "float"  :: "Float"   :: Nil
        case JDouble => "double" :: "Double"  :: Nil
      }

      numericType match {
        case integralType: AbstractIntegralStructMemberType           => matchIntegralType(integralType)
        case floatingPointType: AbstractFloatingPointStructMemberType => matchFloatingPointType(floatingPointType)
      }
    }

    def matchTypeToString(`type`: StructMemberType): Seq[String] = `type` match {
      case JBoolean    => "bool"   :: "boolean" :: "Boolean" :: Nil
      case JString     => "String" ::  Nil
      case SnmmPointer => ???
      case numericType: AbstractNumericStructMemberType => matchNumericType(numericType)
    }

    matchTypeToString(structMemberType)
  }
}
