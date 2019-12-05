package io.cat.ai.snmm.platform.compiler

trait OsSpecificCompiler extends AbstractSnmmCompiler {

  def libExt: String
  def libInclude: String
  def compilerFlag: String
}
