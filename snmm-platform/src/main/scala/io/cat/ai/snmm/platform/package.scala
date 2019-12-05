package io.cat.ai.snmm

import io.cat.ai.snmm.platform.exceptions.PlatformUnknownException

package object platform {

  protected[this] lazy val arch: String = System.getProperty("os.arch")
  protected[this] lazy val os: String = System.getProperty("os.name")

  lazy val $JAVA_HOME: String = System.getenv("JAVA_HOME")
  lazy val $PATH: String = System.getenv("PATH")

  sealed trait OS

  sealed trait POSIX extends OS
  sealed trait MicrosoftWindows extends OS

  final case object Linux extends POSIX
  final case object FreeBSD extends POSIX
  final case object MacOS extends POSIX

  final case object Windows extends MicrosoftWindows
  final case object WindowsNT extends MicrosoftWindows

  def getNativePlatform: NativePlatform = os match {

    case win if win startsWith "Windows" => NativePlatform(Windows, arch)
    case win if win startsWith "WindowsNT" => NativePlatform(WindowsNT, arch)

    case posix if posix startsWith "Linux" => NativePlatform(Linux, arch)
    case posix if (posix startsWith "Mac") || (posix startsWith "Darwin") => NativePlatform(MacOS, arch)
    case posix if posix startsWith "FreeBSD" => NativePlatform(FreeBSD, arch)

    case _ => throw new PlatformUnknownException(s"$os not supported")
  }
}