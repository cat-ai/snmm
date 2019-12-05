package io.cat.ai.snmm.posix.module

import com.google.inject.Provider
import com.typesafe.config.{Config, ConfigFactory}

class PosixConfigProvider extends Provider[Config] {
  override def get: Config = ConfigFactory.load("snmm_posix_config.conf")
}