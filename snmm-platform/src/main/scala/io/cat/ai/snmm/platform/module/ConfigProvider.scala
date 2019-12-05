package io.cat.ai.snmm.platform.module

import com.google.inject.Provider
import com.typesafe.config.{Config, ConfigFactory}

class ConfigProvider extends Provider[Config] {
  override def get: Config = ConfigFactory.load("snmm_core_config.conf")
}