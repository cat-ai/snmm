package io.cat.ai.snmm.windows.module

import com.google.inject.Provider

import com.typesafe.config.{Config, ConfigFactory}

class WindowsConfigProvider extends Provider[Config] {
  override def get: Config = ConfigFactory.load("snmm_windows_config.conf")
}