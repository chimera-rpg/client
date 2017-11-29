-- premake5.lua
solution "chimera"
  configurations { "Debug", "Release" }
  location ("build/" .. _ACTION)

project "interfaceSDL2"
  kind "SharedLib"
  targetprefix ""
  language "C++"
  targetdir "./modules"
  location ("build/" .. _ACTION)
  files { "src/common/Exception.cpp", "src/common/Log.cpp", "src/SDL2/**.cpp" }
  includedirs { "src/" }
  flags { "C++14" }

  configuration { "linux" }
    buildoptions { "-I/usr/include/SDL2/" }
    links { "SDL2", }
    buildoptions { "-DLOG_FORMAT" }

project "chimera-client"
  kind "ConsoleApp"
  language "C++"
  targetdir "./"
  location ("build/" .. _ACTION)

  files { "src/*.cpp", "src/common/**.cpp" }
  includedirs { "src/" }

  flags { "C++14" }

  configuration { "linux" }
    buildoptions { "-I/usr/include/SDL2/" }
    links { "pthread", "dl" }
    buildoptions { "-DLOG_FORMAT" }
  configuration "macosx"
    syslibdirs { "/Library/Frameworks/" }
    libdirs { "/Library/Frameworks/" }
    links { "SDL2.framework" }
    includedirs { "/Library/Frameworks/SDL2.framework/Headers/" }
    sysincludedirs { "/Library/Frameworks/SDL2.framework/Headers/" }
    xcodebuildsettings {
      ["GCC_VERSION"] = "4.8"
    }
  configuration "windows"
    links { "SDL2", "SDL2main", "ws2_32" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    flags { "Symbols" }

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"
