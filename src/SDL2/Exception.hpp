#include <exception>
#include "common/Exception.hpp"

namespace Chimera {
  namespace SDL2 {
    class Exception : public Chimera::Exception {
      public:
        Exception(const std::string &arg, const char *file, int line) : Chimera::Exception(arg, file, line) { }
    };
  }
}
