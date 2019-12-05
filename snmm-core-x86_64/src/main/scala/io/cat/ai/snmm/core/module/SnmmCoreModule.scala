package io.cat.ai.snmm.core.module

import com.google.inject.AbstractModule
import com.google.inject.name.Names

import com.typesafe.config.Config

import net.codingwell.scalaguice.ScalaModule

class SnmmCoreModule extends AbstractModule with ScalaModule {

  override def configure: Unit = bind[Config].annotatedWith(Names.named("coreConfig")).toProvider[ConfigProvider]
}