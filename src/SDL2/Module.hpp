#pragma once
#include "../common/ModuleSupport.hpp"

namespace Chimera {
  namespace SDL2 {
    class Module : public Chimera::Module {
      public:
        Module();
        ~Module();
        void init();
        void close();
        void tick();
      private:
        SDL_Window *mWindow;
        SDL_Renderer *mRenderer;
    };
  }
}

extern "C" DLL_PUBLIC Chimera::Module* instantiate();
