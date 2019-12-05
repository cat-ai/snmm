package io.cat.ai.snmm.macros.debug

import scala.annotation.StaticAnnotation
import scala.language.experimental.macros
import scala.reflect.macros.whitebox

object MacroExpander {

  class expand_macro extends StaticAnnotation {
    def macroTransform(annottees: Any*): Any = macro ExpanderImpl.apply
  }

  class ExpanderImpl(val c: whitebox.Context) {

    import c.universe._

    def expandImpl(s: String): Unit =
      c.info(c.enclosingPosition, s.split("\n").mkString("\n |--- :: Expanded macro tree :: ---\n |", "\n |", ""), force = true)

    def apply(annottees: c.Expr[Any]*): c.Expr[Any] = {
      val a: Seq[c.universe.Tree] = annottees.map(_.tree)
      expandImpl(show(a.head))
      c.Expr[Any](Block(a.toList, Literal(Constant(()))))
    }
  }
}
