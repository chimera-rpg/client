#pragma once
#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

#if defined(_WIN32)
#define DYN_EXT ".dll"
#elif defined(__APPLE__)
#define DYN_EXT ".dylib"
#elif defined(unix) || defined(__unix__) || defined(__unix)
#define DYN_EXT ".so"
#endif

#ifndef DYN_EXT
#error "No dynamic library extension defined for this operating system. Check ModuleSupport.hpp and Client.cpp for adding OS support."
#endif

#include <cstdint>

namespace Chimera {
  class Module {
    public:
      Module() {};
      ~Module() {};
      virtual void init() { };
      virtual void close() { };
      virtual void tick() { };
  };
  typedef Module* (*ModuleCtor)();
}
