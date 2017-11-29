#include "common/Client.hpp"
#include "common/Log.hpp"
#include "common/ModuleSupport.hpp"
#include "common/ModuleException.hpp"
#include "common/PlatformSupport.hpp"

#if PLATFORM == UNIX || PLATFORM == MACOS
#include <dlfcn.h>
#endif

namespace Chimera {
  Client::Client() {
  }
  Client::~Client() {
    if (mInterface != nullptr) {
      mInterface->close();
    }
  }
  void Client::initialize() {
    try {
      mInterface = loadModule(mCfg.get("modulesDir")+OS_SLASH+"interface"+mCfg.get("interfaceModule"));
    } catch (ModuleException& e) {
      ERR << e.what();
      throw(e);
    }
    mInterface->init();
  }
  void Client::tick() {
    mInterface->tick();
  }
  void Client::loop() {
    for (;;) {
      tick();
    }
  }

  Chimera::Module* Client::loadModule(std::string filename) {
    LOG << "Loading Module:" << filename;
#if PLATFORM == WINDOWS
    Chimera::ModuleCtor ctor;

    HINSTANCE mHandle;

    std::wstring wFilename = s2ws(filename + DLL_EXT);

    mHandle = LoadLibrary(wFilename.c_str());
    if (mHandle == nullptr) {
      THROW(ModuleException, GetLastErrorAsString());
    }
    ctor = reinterpret_cast<Chimera::ModuleCtor>(GetProcAddress(mHandle, "instantiate"));
    if (ctor == NULL) {
      THROW(ModuleException, GetLastErrorAsString());
    }
    return ctor();
#elif PLATFORM == MACOS || PLATFORM == UNIX
    char *error;
    void *mHandle;
    Chimera::ModuleCtor ctor;

    mHandle = dlopen((filename + DLL_EXT).c_str(), RTLD_LAZY);
    if (mHandle == nullptr) {
      THROW(ModuleException, dlerror());
    }
    dlerror();

    ctor = reinterpret_cast<Chimera::ModuleCtor>(dlsym(mHandle, "instantiate"));
    if ((error = dlerror()) != NULL) {
      THROW(ModuleException, error);
    }
    return ctor();
#endif
  }
}
