package io.cat.ai.snmm.posix.compiler.linux

import com.typesafe.config.Config

import io.cat.ai.snmm.platform.compiler.OsSpecificCompiler

abstract class AbstractLinuxCompiler(conf: Config) extends OsSpecificCompiler {

  override def libExt: String = conf.getString("platform.posix.linux.libExt")
  override def libInclude: String = conf.getString("platform.posix.linux.jni.include")
  override def compilerFlag: String = conf.getString("platform.posix.linux.compiler.gcc.flag")
}