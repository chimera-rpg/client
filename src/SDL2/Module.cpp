#include <SDL.h>
#include "SDL2/Module.hpp"
#include "SDL2/Exception.hpp"
#include "common/Log.hpp"

namespace Chimera {
  namespace SDL2 {
    Module::Module() {
    }
    Module::~Module() {
    }
    void Module::init() {
      if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        THROW(Exception, SDL_GetError());
      }

      mWindow = SDL_CreateWindow("Chimera SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

      if (mWindow == NULL) {
        THROW(Exception, SDL_GetError());
      }
    }
    void Module::close() {
      SDL_DestroyWindow(mWindow);
      SDL_Quit();
    }
    void Module::tick() {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          THROW(Exception, SDL_GetError());
        }
      }
    }
  }
}

DLL_PUBLIC Chimera::Module* instantiate() {
  return new Chimera::SDL2::Module();
}
