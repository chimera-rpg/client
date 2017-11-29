#pragma once
#include <stdexcept>
#include <iostream>
#include <string>

namespace Chimera {
  class Exception : public std::runtime_error {
    private:
      static std::string out;
    protected:
      std::string mText;
      std::string mFile;
      int mLine;
    public:
      Exception(const std::string &arg, const char *file, int line) : std::runtime_error(arg), mText(arg), mFile(file), mLine(line) {}
      const char *what() const throw() {
        out = mFile + ":" + std::to_string(mLine) + ": " + mText;
        return out.c_str();
      }
  };
#define THROW(type, arg) throw type(arg, __FILE__, __LINE__);
}
