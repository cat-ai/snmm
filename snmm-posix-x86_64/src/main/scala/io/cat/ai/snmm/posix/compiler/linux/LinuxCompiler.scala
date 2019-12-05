package io.cat.ai.snmm.posix.compiler.linux

import com.google.inject.Inject

import com.typesafe.config.Config

class LinuxCompiler @Inject()(conf: Config) extends AbstractLinuxCompiler(conf) {

  override def compile: Boolean = throw new NotImplementedError("Compiler API not implemented yet!")

  def load: Unit = System.load(conf.getString("snmm.platform.posix.linux.nativeLib.path"))
}