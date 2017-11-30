#include <SDL.h>
#include <string>
#include "common/ModuleException.hpp"
#include "SDL2/Module.hpp"
#include "common/Log.hpp"

namespace Chimera {
  namespace SDL2 {
    Module::Module() {
    }
    Module::~Module() {
    }
    void Module::init() {
      int width, height, x, y;
      if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        THROW(Chimera::ModuleException, SDL_GetError());
      }

      width   = std::stoi(requestValue("window_width"));
      height  = std::stoi(requestValue("window_height"));
      x       = std::stoi(requestValue("window_x")) || SDL_WINDOWPOS_UNDEFINED;
      y       = std::stoi(requestValue("window_y")) || SDL_WINDOWPOS_UNDEFINED;

      mWindow = SDL_CreateWindow("Chimera SDL2", x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

      if (mWindow == NULL) {
        THROW(Chimera::ModuleException, SDL_GetError());
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
          THROW(Chimera::ModuleException, "Quit");
        }
      }
    }
  }
}

DLL_PUBLIC Chimera::Module* instantiate() {
  return new Chimera::SDL2::Module();
}
