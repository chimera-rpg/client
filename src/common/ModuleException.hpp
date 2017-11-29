#pragma once
#include "Exception.hpp"

namespace Chimera { 
  class ModuleException : public Exception {
    public:
      ModuleException(const std::string &arg, const char *file, int line) : Chimera::Exception(arg, file, line) {};
  };
}
