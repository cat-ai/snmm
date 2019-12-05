package io.cat.ai.snmm.posix.jni

import com.google.inject.Inject
import com.google.inject.name.Named

import com.typesafe.config.Config

import io.cat.ai.snmm.platform
import io.cat.ai.snmm.platform.{Linux, MacOS, NativePlatform}
import io.cat.ai.snmm.platform.util.NativeLibLoader

class SnmmPosixJni @Inject() (@Named("posixConfig") conf: Config) extends NativeLibLoader {

  override def load: Unit = platform.getNativePlatform match {

    case NativePlatform(Linux, _) => System.load(conf.getString("snmm.platform.posix.linux.nativeLib.path"))

    case NativePlatform(MacOS, _) => System.load(conf.getString("snmm.platform.posix.mac.nativeLib.path"))

    case NativePlatform(other, _) => throw new UnsupportedOperationException(s"$other is not supported!")
  }
}

object SnmmPosixJni {

  private val cPosixJniInstance: SnmmPosixMman = new SnmmPosixMman()

  final val POSIX_MMAN: SnmmPosixMman = cPosixJniInstance
}