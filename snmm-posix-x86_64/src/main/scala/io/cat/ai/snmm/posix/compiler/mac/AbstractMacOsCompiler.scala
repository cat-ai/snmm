package io.cat.ai.snmm.posix.compiler.mac

import com.typesafe.config.Config

import io.cat.ai.snmm.platform.compiler.OsSpecificCompiler

abstract class AbstractMacOsCompiler(conf: Config) extends OsSpecificCompiler {

  override def libExt: String = conf.getString("platform.posix.macos.lib_ext")
  override def libInclude: String = conf.getString("platform.posix.macos.jni.include")
  override def compilerFlag: String = conf.getString("platform.posix.macos.compiler.gcc.flag")
}