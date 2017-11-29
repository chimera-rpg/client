#include <string>
#include <memory>
#include "common/Client.hpp"
#include "common/Log.hpp"
#include "common/ModuleException.hpp"

int main(int argc, char *argv[]) {
  auto client = std::make_unique<Chimera::Client>();
  // set all our defaults
  client->mCfg.set("interfaceModule", "SDL2");
  client->mCfg.set("macros", "interfaceSDL2");
  client->mCfg.set("default_width", 1024);
  client->mCfg.set("default_height", 768);
  client->mCfg.set("default_x", -0);
  client->mCfg.set("default_y", -0);
  client->mCfg.set("modulesDir", "modules");
  // parse args
  // read user's settings
  client->mCfg.readFromFilename("client.cfg");
  // Attempt to load client module
  try {
    client->initialize();
  } catch(Chimera::ModuleException& e) {
    ERR << e.what();
    throw(e);
  }
  client->loop();
  
  return 0;
}
