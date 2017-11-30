#include <string>
#include <memory>
#include <exception>
#include "common/Client.hpp"
#include "common/Log.hpp"
#include "common/ModuleException.hpp"
#include "dialog/Dialog.hpp"

void terminateHandler() {
  Chimera::ErrorDialog("Uncaught Error", "An error was unhandled.");
  std::abort();
}

int main(int argc, char *argv[]) {
  std::set_terminate(terminateHandler);
  auto client = std::make_unique<Chimera::Client>();
  // set all our defaults
  client->mCfg.set("modulesDir", "modules");
  client->mCfg.set("interfaceModule", "SDL2");
  client->mCfg.set("window_width", 1024);
  client->mCfg.set("window_height", 768);
  // parse args
  // read user's settings
  client->mCfg.readFromFilename("client.cfg");
  // Attempt to load client module
  try {
    client->initialize();
    client->loop();
  } catch(Chimera::ModuleException& e) {
    Chimera::ErrorDialog("Module Error", e.what());
    return 1;
  }
  return 0;
}
