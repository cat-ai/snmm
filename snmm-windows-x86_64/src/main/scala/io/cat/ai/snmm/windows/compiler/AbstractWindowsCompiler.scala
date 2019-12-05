package io.cat.ai.snmm.windows.compiler

import com.typesafe.config.Config

import io.cat.ai.snmm.platform.compiler.OsSpecificCompiler

abstract class AbstractWindowsCompiler(conf: Config) extends OsSpecificCompiler {

  override def libExt: String = conf.getString("snmm.platform.msWindows.windows.libExt")
  override def libInclude: String = conf.getString("snmm.platform.msWindows.windows.jni.include")
  override def compilerFlag: String = conf.getString("snmm.platform.msWindows.windows.compiler.gcc.flag")
}