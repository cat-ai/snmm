package io.cat.ai.snmm.core.jni

import com.google.inject.Inject
import com.google.inject.name.Named

import com.typesafe.config.Config

import io.cat.ai.snmm.platform._
import io.cat.ai.snmm.platform.util.NativeLibLoader

class SnmmCore @Inject() (@Named(value="coreConfig") conf: Config) extends NativeLibLoader {

  private def loadPosixCoreNativeLib(posix: POSIX): Unit = posix match {

    case Linux => System.load(conf.getString("snmm.platform.posix.linux.nativeLib.path"))

    case MacOS => ??? // TODO

    case FreeBSD => ???
  }

  private def loadMsWindowsCoreNativeLib(msWindows: MicrosoftWindows): Unit = msWindows match {

    case Windows => System.load(conf.getString("snmm.platform.msWindows.windows.nativeLib.path"))

    case WindowsNT => throw new UnsupportedOperationException("WindowsNT not supported!")
  }

  override def load: Unit = getNativePlatform match {

    case NativePlatform(posix: POSIX, _) => loadPosixCoreNativeLib(posix)

    case NativePlatform(msWindows: MicrosoftWindows, _) => loadMsWindowsCoreNativeLib(msWindows)
  }
}

object SnmmCore {

  private val snmmCoreJniInstance: SnmmCoreJni = new SnmmCoreJni()

  final val SNMM_CORE_JNI: SnmmCoreJni = snmmCoreJniInstance
}