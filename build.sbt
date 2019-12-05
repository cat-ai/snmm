name := "snmm"

organization := "cat-ai"

scalaVersion in ThisBuild := "2.13.0"

import sbt._
import Keys._

val paradiseVersion = "2.1.0"

val buildSettings = Defaults.coreDefaultSettings ++ Seq(
  organization := "org.scalamacros",
  version := "1.0.0",
  scalacOptions ++= Seq(),
  scalaVersion := "2.12.4",
  crossScalaVersions := Seq("2.10.2", "2.10.3", "2.10.4", "2.10.5", "2.10.6",
    "2.11.0", "2.11.1", "2.11.2", "2.11.3", "2.11.4",
    "2.11.5", "2.11.6", "2.11.7", "2.11.8",
    "2.12.0", "2.12.1", "2.12.2", "2.12.3", "2.12.4"),
  resolvers += Resolver.sonatypeRepo("snapshots"),
  resolvers += Resolver.sonatypeRepo("releases"),
  addCompilerPlugin("org.scalamacros" % "paradise" % paradiseVersion cross CrossVersion.full)
)

scalacOptions += "-Ymacro-debug-lite"

lazy val root: Project = Project("root", file("."),
  settings = buildSettings ++ Seq(
    run := (run in Compile in snmmCoreX86_64).evaluated
  )
) aggregate(snmmPlatform, snmmMacros, snmmCoreX86_64, snmmWindowsX86_64, snmmPosixX86_64)

lazy val snmmPlatform: Project = Project("snmm-platform", file("snmm-platform"),
  settings = buildSettings ++ Seq(
    libraryDependencies += "com.typesafe" % "config" % "1.3.1",
    libraryDependencies += "net.codingwell" %% "scala-guice" % "4.2.6"
  )
)

lazy val snmmMacros: Project = Project("snmm-macros", file("snmm-macros"),
  settings = buildSettings ++ Seq(
    libraryDependencies += scalaVersion("org.scala-lang" % "scala-reflect" % _).value,
    libraryDependencies ++= (
      if (scalaVersion.value.startsWith("2.10")) List("org.scalamacros" %% "quasiquotes" % paradiseVersion)
      else Nil
      )
  )
) dependsOn snmmPlatform

lazy val snmmCoreX86_64: Project = Project("snmm-core-x86_64", file("snmm-core-x86_64"),
  settings = buildSettings ++ Seq(
    libraryDependencies += "com.typesafe" % "config" % "1.3.1",
    libraryDependencies += "net.codingwell" %% "scala-guice" % "4.2.6"
  )
) dependsOn(snmmMacros, snmmPlatform)

lazy val snmmPosixX86_64: Project = Project("snmm-posix-x86_64", file("snmm-posix-x86_64"),
  settings = buildSettings
) dependsOn(snmmCoreX86_64, snmmPlatform)

lazy val snmmWindowsX86_64: Project = Project("snmm-windows-x86_64", file("snmm-windows-x86_64"),
  settings = buildSettings
) dependsOn(snmmCoreX86_64, snmmPlatform)