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

#include <cstdint>
#include <functional>

namespace Chimera {
  class Module {
    public:
      typedef std::function<void(const std::string &key, const std::string &value)> StoreValueFunc;
      typedef std::function<std::string(const std::string &key)> RequestValueFunc;
      Module() {};
      ~Module() {};
      virtual void init() { };
      virtual void close() { };
      virtual void tick() { };
      /* These function pointers are assigned by the Client to the corresponding handlers upon module load. */
      StoreValueFunc storeValue;
      RequestValueFunc requestValue;
  };
  typedef Module* (*ModuleCtor)();
}
