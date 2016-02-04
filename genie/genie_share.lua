-- Define the project. Put the release configuration first so it will be the
-- default when folks build using the makefile. That way they don't have to
-- worry about the /scripts argument and all that.
--
	--premake.make.override = { "TARGET" }

solution "ROTOM"
  configurations { "Release", "Debug" }
  location (_OPTIONS["to"])
  
  configuration "Debug"
    defines     { "_DEBUG", "LUA_COMPAT_MODULE" }
    flags       { "Symbols" }
    debugdir "../project_share/build/bin/debug"
    os.mkdir "../project_share/build/bin/debug"

  configuration "Release"
    defines     { "NDEBUG", "LUA_COMPAT_MODULE" }
    flags       { "OptimizeSize" }
    debugdir "../project_share/build/bin/release"
    os.mkdir "../project_share/build/bin/release"

  configuration "vs*"
    defines     { "_CRT_SECURE_NO_WARNINGS" }

  configuration "windows"
    targetdir "../project_share/build/bin/windows"

--
-- Use the --to=path option to control where the project files get generated. I use
-- this to create project files for each supported toolset, each in their own folder,
-- in preparation for deployment.
--
	newoption {
		trigger = "to",
		value   = "path",
		description = "Set the output location for the generated files"
	}
  
  os.mkdir("../project_share/build/bin/windows")
  os.copyfile("../lib/openal32.dll", "../project_share/build/bin/windows/openal32.dll")
  os.copyfile("../lib/openal32.lib", "../project_share/build/bin/windows/openal32.lib")
  os.copyfile("../project/build/bin/windows/ROTOM.lib", "../project_share/build/bin/windows/ROTOM.lib")

--[[--------------------------------------------
------------- EXAMPLES AND TESTING -------------
--]]--------------------------------------------
project "ROTOM_testing"
  targetname "ROTOM_testing"
  language "C++"
  location "../project_share/build"
	libdirs "../project_share/build/bin/windows"
  kind "ConsoleApp"
  
  links {
    "opengl32",
    "openal32",
    "ROTOM",
  }
  
  includedirs {
    "../include",
    "../deps/glm",
    "../deps/imgui",
  }
  
  excludes {
	"../include/security.h",
	"../include/graphics.h",
  }
  
  files {
    "../img/*.*",
    "../include/*.h",
    "../examples/*.cc",
    "../deps/imgui/*.cpp",
  }