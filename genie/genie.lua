--
-- ////////////////////////////////////////////
-- /////Autor: Juan Daniel Laserna Condado/////
-- /////Email: lasernaco@esat-alumni.com  /////
-- /////            2015-2016             /////
-- ////////////////////////////////////////////
--

-- Define the project. Put the release configuration first so it will be the
-- default when folks build using the makefile. That way they don't have to
-- worry about the /scripts argument and all that.
--

solution "ROTOM"
  configurations { "Release", "Debug" }
  location (_OPTIONS["to"])
  
  configuration "Debug"
    defines     { "_DEBUG", "LUA_COMPAT_MODULE" }
    flags       { "Symbols" }
    debugdir "../project/build/bin/debug"
    os.mkdir "../project/build/bin/debug"

  configuration "Release"
    defines     { "NDEBUG", "LUA_COMPAT_MODULE" }
    flags       { "OptimizeSize" }
    debugdir "../project/build/bin/release"
    os.mkdir "../project/build/bin/release"

  configuration "vs*"
    defines     { "_CRT_SECURE_NO_WARNINGS" }

  configuration "windows"
    targetdir "../project/build/bin/windows"

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
  
  os.mkdir("../project/build/bin/windows")
  os.copyfile("../lib/openal32.dll", "../project/build/bin/windows/openal32.dll")
  os.copyfile("../lib/openal32.lib", "../project/build/bin/windows/openal32.lib")

--[[--------------------------------------------
------------- EXAMPLES AND TESTING -------------
--]]--------------------------------------------
project "ROTOM_testing"
  targetname "ROTOM_testing"
  language "C++"
  location "../project/build"
	libdirs "../project/build/bin/windows"
  kind "ConsoleApp"
  
  links {
    "opengl32",
    "openal32",
    "ROTOM",
    "ROTOM_tool_meshLoader",
  }
  
  includedirs {
    "../include",
    "../tools/meshLoader/include",
    "../examples/include",
    "../deps/glm",
    "../deps/imgui",
  }
  
  files {
    "../img/**.*",
    "../obj/**.*",
    "../shaders/**.*",
    "../include/**.h",
    "../examples/**.*",
    "../deps/imgui/*.cpp",
    "../tools/meshLoader/include/**.h",
  }

--[[--------------------------------------------
----------------- ROTOM ENGINE -----------------
--]]--------------------------------------------
project "ROTOM"
  targetname "ROTOM"
  language "C++"
  location "../project/build"
	libdirs "../lib"
  kind "StaticLib"
  
  --[[flags {
    "No64BitChecks",
    "ExtraWarnings",
  }]]
  
  links {
    "opengl32",
    "openal32",
  }

  defines {
    "_GLFW_WIN32",
    "_GLFW_WGL",
    "_GLFW_USE_OPENGL",
  }
  
  includedirs {
    "../include",
    "../tools/meshLoader/include",
    "../deps/glew/include",
    "../deps/glfw/include",
    "../deps/glm",
    "../deps/imgui",
    "../deps/openal/include",
    "../deps/soil",
    "../deps/stb",
  }
  
  files {
    "../include/**.h",
    "../src/**.cc",
    "../deps/glew/src/glew.c",
    "../deps/glfw/src/*.c",
    "../deps/imgui/*.cpp",
    "../deps/soil/*.c",
    "../deps/stb/*.c",
    "../tools/meshLoader/include/**.h",
  }

--[[--------------------------------------------
-------------- TOOL - Mesh_Loader --------------
--]]--------------------------------------------
project "ROTOM_tool_meshLoader"
  targetname "ROTOM_tool_meshLoader"
  language "C++"
  location "../project/build"
	libdirs "../project/build/bin/windows"
  kind "StaticLib"
  
  links {
    "opengl32",
    "openal32",
    "ROTOM",
  }
  
  includedirs {
    "../include",
    "../deps/glm",
    "../deps/imgui",
    "../tools/meshLoader/include",
    "../deps/tinyobjloader",
  }
  
  files {
    "../img/**.*",
    "../obj/**.*",
    "../shaders/**.*",
    "../include/**.h",
    "../tools/meshLoader/include/**.h",
    "../tools/meshLoader/src/**.cc",
    "../deps/imgui/*.cpp",
    "../deps/tinyobjloader/*.cc",
  }