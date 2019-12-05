package io.cat.ai.snmm.macros.struct

import scala.annotation.{StaticAnnotation, compileTimeOnly}
import scala.language.postfixOps
import scala.language.experimental.macros
import scala.reflect.macros.whitebox

object SnmmStructMacro {

  @compileTimeOnly("enable macro paradise")
  class struct extends StaticAnnotation {
    def macroTransform(annottees: Any*): Any = macro RawStruct.impl
  }

  @compileTimeOnly("enable macro paradise")
  class offheap_alloc extends StaticAnnotation {
    def macroTransform(annottees: Any*): Any = macro SnmmStructAllocMacro.impl
  }

  protected[macros] object RawStruct {

    def impl(c: whitebox.Context)(annottees: c.Tree*): c.Tree = {

      import c.universe._

      annottees match {

        case q"$m class $tpename[..$tpearams] $ctorMods(...$paramss) extends { ..$earlydefns } with ..$parents { $self => ..$stats }" :: tail =>

          q"""
              import io.cat.ai.snmm.CSyntax._
              import io.cat.ai.snmm.stdlib._
              import io.cat.ai.snmm.Implicits._
              import io.cat.ai.snmm.core.pointer.struct.utils.Util._
            """

          val members: Seq[c.universe.Tree] = paramss.flatten.map {
            case q"$_ val $tname: $tpt = $_" =>
              q"""
                 StructMember(parseTypeAsStringToStructMember(${tpt.toString}), ${tname.toString}, 0, sizeof[$tpt])
                """
          }

          q"""
             import io.cat.ai.snmm.core.pointer.struct.{AbstractStruct, StructMember}
             import io.cat.ai.snmm.core.pointer.struct.utils.Util._

             $m class $tpename[..$tpearams] $ctorMods(...$paramss) extends { ..$earlydefns } with ..${tq"AbstractStruct" :: parents} { $self =>

               override def structMembers: _root_.scala.collection.Seq[StructMember] = assignPositionToMembers(_root_.scala.collection.Seq.apply(..$members))

               ..$stats
             }

           ..$tail
          """
      }
    }
  }

  protected[macros] object SnmmStructAllocMacro {

    def impl(c: whitebox.Context)(annottees: c.Tree*): c.Tree = {

      import c.universe._

      annottees match {

        case q"$m class $tpename[..$tpearams] $ctorMods(...$paramss) extends { ..$earlydefns } with ..$parents { $self => ..$stats }" :: tail =>

          q"""
             import io.cat.ai.snmm.stdlib._
             import io.cat.ai.snmm.StructImplicits._
             import io.cat.ai.snmm.core.pointer.{NULL, NativePointer, Pointer}
             import io.cat.ai.snmm.core.pointer.struct._
             import io.cat.ai.snmm.core.pointer.struct.utils._
             import io.cat.ai.snmm.core.pointer.struct.{AbstractStruct, StructMember}
           """

          val structMembersSeq =
            for (q"$_ def $methodName: $_ = $body" <- stats if s"$methodName" == "structMembers") yield body

          q"""
             import io.cat.ai.snmm.stdlib._
             import io.cat.ai.snmm.Implicits._
             import io.cat.ai.snmm.core.pointer.{NULL, NativePointer, Pointer}
             import io.cat.ai.snmm.core.pointer.struct
             import io.cat.ai.snmm.core.pointer.struct._
             import io.cat.ai.snmm.core.pointer.struct.utils._
             import io.cat.ai.snmm.core.pointer.struct.{AbstractStruct, StructMember}
             import io.cat.ai.snmm.core.pointer.struct.StructTypes._

             protected[this] val structMemberss = _root_.scala.collection.Seq.apply(..$structMembersSeq).flatten

             protected[this] def structMembersCount: Map[StructMemberType, Int] =
                               structMemberss
                                 .groupBy(_.structMemberType)
                                 .map {
                                   case (structMemberType, seq) =>
                                     (structMemberType, seq.map(_.structMemberType).count(_ == structMemberType))
                                 }

             protected[this] val keyCount: Int = structMembersCount.keySet.size
             protected[this] val offheapAddress = io.cat.ai.snmm.core.pointer.struct.alloc(keyCount)

             structMembersCount.foreach { case (structMemberType, count) => putKeyTypeToStruct(structMemberType, count, offheapAddress) }

             $m class $tpename[..$tpearams] $ctorMods(...$paramss) extends {..$earlydefns } with ..$parents with Pointer[Unit] { $self =>

               import io.cat.ai.snmm.Implicits._
               import io.cat.ai.snmm.CSyntax._
               import io.cat.ai.snmm.core.pointer.generic.{NativeHeapPointer, NativeSize}

               override def address: Long = offheapAddress

               override def close: Unit = struct.freeStruct(this)

               def *->[A](ptrPosPair: (Long, Pointer[A], Int))
                                      (implicit nativeHeapPointer: NativeHeapPointer[A], nativeSize: NativeSize[A]): A = ptrPosPair match {

                  case (0, NULL, _) | (_, NULL, _) => throw new NullPointerException("NULL")

                  case (baseOffheadpAddress, ptr, pos) =>
                    if (this.address == baseOffheadpAddress )
                      *[A](ptr + pos)
                    else
                      throw new RuntimeException(s"Invalid pointer address $$baseOffheadpAddress")
               }

               def ->[A](ptrPosPair: (Long, Pointer[A], Int))
                                      (implicit
                                        nativeHeapPointer: NativeHeapPointer[A],
                                        nativeSize: NativeSize[A]): Pointer[A] = ptrPosPair match {

                   case (0, NULL, _) | (_, NULL, _) => throw new NullPointerException("NULL")

                   case (baseOffheadpAddress, ptr, pos) =>
                     if (this.address == baseOffheadpAddress )
                       (ptr + pos)
                     else
                       throw new RuntimeException(s"Invalid pointer address $$baseOffheadpAddress")
             }

             ..$stats

             }

             object ${tpename.toTermName} {

                import io.cat.ai.snmm.StructImplicits._
                import io.cat.ai.snmm.core.pointer.{NULL, NativePointer, Pointer}
                import io.cat.ai.snmm.core.pointer.struct
                import io.cat.ai.snmm.core.pointer.struct.utils._
                import io.cat.ai.snmm.core.pointer.struct.{AbstractStruct, StructMember}

             ..${
               paramss
                 .flatten
                 .map {
                   case q"$_ val $tname: $tpt = $value" =>
                     q"""
                         structMemberss.find(_.structMemberName == ${tname.toString}) match {

                           case Some(memberr) => struct.putStructMember[$tpt]($value, memberr.pos, offheapAddress)

                           case None => ()
                         }
                       """
                  }
             }

             ..${
               paramss
                 .flatten
                 .map {
                   case q"$_ val $tname: $tpt = $_" =>

                     q"""
                         def $tname: (Long, Pointer[$tpt], Int) = structMemberss.find(_.structMemberName == ${tname.toString}) match {

                           case Some(memberr) => (offheapAddress, struct.getStructMember[$tpt](memberr.pos, offheapAddress), memberr.pos)

                           case _ => (0, NULL, 0)
                         }
                       """
                   }
                }
             }

             ..$tail
            """
      }
    }
  }
}