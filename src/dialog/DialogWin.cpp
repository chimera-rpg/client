#include "dialog/Dialog.hpp"
#include "common/PlatformSupport.hpp"

namespace Chimera {
  void ErrorDialog(const std::string &title, const std::string &message) {
    MessageBox(NULL, s2ws(message).c_str(), s2ws(title).c_str(), MB_SYSTEMMODAL|MB_ICONERROR|MB_SETFOREGROUND|MB_TOPMOST);
  }
}
