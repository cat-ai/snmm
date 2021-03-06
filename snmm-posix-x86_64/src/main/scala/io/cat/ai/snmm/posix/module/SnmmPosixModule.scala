package io.cat.ai.snmm.posix.module

import com.google.inject.AbstractModule
import com.google.inject.name.Names

import com.typesafe.config.Config

import net.codingwell.scalaguice.ScalaModule

class SnmmPosixModule extends AbstractModule with ScalaModule {

  override def configure: Unit = {
    bind[Config].annotatedWith(Names.named("posixConfig")).toProvider[PosixConfigProvider]
  }
}