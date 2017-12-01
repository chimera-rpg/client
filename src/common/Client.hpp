#pragma once
#include <memory>
#include "common/Cfg.hpp"

/* Forward declarations */
namespace Chimera {
  class Module;
}

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
      void bindModule(Chimera::Module *module);
    private:
      Chimera::Module* mInterface{nullptr};
      Chimera::Module* mMacros{nullptr};
      Chimera::Module* mNetwork{nullptr};
  };
}
