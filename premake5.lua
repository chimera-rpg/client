-- premake5.lua
solution "chimera"
  configurations { "Debug", "Release" }
  location ("build/" .. _ACTION)

project "chimera-client"
  kind "ConsoleApp"
  language "C++"
  targetdir "./"
  location ("build/" .. _ACTION)

  files { "src/*.cpp", "src/common/**.cpp" }
  includedirs { "src/" }

  cppdialect "C++14"
  xcodebuildsettings {
    ["OTHER_CFLAGS"] = "--std=c++1z"
  }

  configuration { "linux" }
    buildoptions { "-I/usr/include/SDL2/" }
    links { "pthread", "dl", "X11" }
    files { "src/dialog/DialogX11.cpp" }
    buildoptions { "-DLOG_FORMAT" }
  configuration "macosx"
    files { "src/dialog/DialogMac.mm" }
    links { "Cocoa.framework" }

  configuration "windows"
    links { "SDL2", "SDL2main", "ws2_32" }

  filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

  filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"

project "interfaceSDL2"
  kind "SharedLib"
  targetprefix ""
  language "C++"
  targetdir "./modules"
  location ("build/" .. _ACTION)
  files { "src/common/Exception.cpp", "src/common/Log.cpp", "src/SDL2/**.cpp" }
  includedirs { "src/" }
  cppdialect "C++14"
  xcodebuildsettings {
    ["OTHER_CFLAGS"] = "--std=c++1z"
  }

  configuration "windows"
    links { "SDL2", "SDL2main", "ws2_32" }
    buildoptions { "-DBUILDING_DLL" }
  configuration { "linux" }
    buildoptions { "-I/usr/include/SDL2/" }
    links { "SDL2" }
    buildoptions { "-DLOG_FORMAT" }
  configuration "macosx"
    links { "SDL2.framework" }
    sysincludedirs { "/Library/Frameworks/SDL2.framework/Headers/" }
    buildoptions {"-F /Library/Frameworks"}
    linkoptions {"-F /Library/Frameworks"}
