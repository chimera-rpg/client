#pragma once
#include <memory>
#include "common/Cfg.hpp"
#include "common/ModuleSupport.hpp"

namespace Chimera {
  class Client {
    public:
      Client();
      ~Client();
      void initialize();
      void tick();
      void loop();
      Cfg mCfg;
      Chimera::Module* loadModule(std::string filename);
    private:
      Chimera::Module* mInterface{nullptr};
      Chimera::Module* mMacros{nullptr};
      Chimera::Module* mNetwork{nullptr};
  };
}
