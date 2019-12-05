package io.cat.ai.snmm.windows.compiler

import com.google.inject.Inject

import com.typesafe.config.Config

class WindowsCompiler @Inject()(conf: Config) extends AbstractWindowsCompiler(conf) {

  override def compile: Boolean = throw new UnsupportedOperationException("Compiler API not implemented yet!")
}