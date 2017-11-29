#include "common/Client.hpp"
#include "common/Log.hpp"
#include "common/ModuleSupport.hpp"
#include "common/ModuleException.hpp"
#include <dlfcn.h>

namespace Chimera {
  Client::Client() {
  }
  Client::~Client() {
    if (interface != nullptr) {
      interface->close();
    }
  }
  void Client::initialize() {
    try {
      interface = loadModule(mCfg.get("modulesDir")+"/interface"+mCfg.get("interfaceModule"));
    } catch (ModuleException& e) {
      ERR << e.what();
      throw(e);
    }
    interface->init();
  }
  void Client::tick() {
    interface->tick();
  }
  void Client::loop() {
    for (;;) {
      tick();
    }
  }

  Chimera::Module* Client::loadModule(std::string filename) {
    char *error;
    void *mHandle;
    Chimera::ModuleCtor ctor;

    mHandle = dlopen((filename+DYN_EXT).c_str(), RTLD_LAZY);
    if (mHandle == nullptr) {
      THROW(ModuleException, dlerror());
    }
    dlerror(); // Clear any existing error.

    ctor = reinterpret_cast<Chimera::ModuleCtor>(dlsym(mHandle, "instantiate"));
    if ((error = dlerror()) != NULL) {
      THROW(ModuleException, error);
    }
    return ctor();
  }
}
