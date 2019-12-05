package io.cat.ai.snmm.windows.jni

import com.google.inject.Inject
import com.google.inject.name.Named

import com.typesafe.config.Config

import io.cat.ai.snmm.platform
import io.cat.ai.snmm.platform.{NativePlatform, Windows, WindowsNT}
import io.cat.ai.snmm.platform.util.NativeLibLoader

class SnmmWindowsJni @Inject() (@Named("windowsConfig") conf: Config) extends NativeLibLoader {

  override def load: Unit = platform.getNativePlatform match {

    case NativePlatform(Windows, _) => System.load(conf.getString("snmm.platform.msWindows.windows.nativeLib.path"))

    case NativePlatform(WindowsNT, _) => throw new UnsupportedOperationException("WindowsNT is not supported")
  }
}

object SnmmWindowsJni {

  private val windowsMemoryApi: win_memman_jni = new win_memman_jni()

  final val WINDOWS_MEMORY_API: win_memman_jni = windowsMemoryApi
}