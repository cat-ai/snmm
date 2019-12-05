package io.cat.ai.snmm.posix.compiler.mac

import java.io.File

import com.google.inject.Inject
import com.typesafe.config.Config

class MacOSCompiler @Inject()(conf: Config) extends AbstractMacOsCompiler(conf) {

  val srcPath: String = ???
  val libPath: String = ???
  val libName: String = ???

  override def compile: Boolean = throw new UnsupportedOperationException("Compiler API not implemented yet!")

  def load: Unit = {
    val path = conf.getString("snmm.platform.posix.mac.nativeLib.path")
    val file = new File(path)

    if (!file.exists()) {
      System.load(path)
    }
  }
}