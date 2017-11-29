/* ================================================================
Log
----------------
This header file describes the Log class
================================================================ */
#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <string>

#include <functional>
#include <map>

namespace Chimera { 
  #ifdef _MSC_VER // Visual Studio
  #define FUNC_NAME __FUNCTION__
  #else // GCC/clang
  #define FUNC_NAME __PRETTY_FUNCTION__
  #endif
  
  enum LogLevel { LOG_INFO, LOG_FAIL, LOG_ERROR, LOG_WARNING, LOG_DEBUG };
  
  extern std::map<LogLevel, std::function<void(const std::string, const std::string)>> gLogHooks;
  
  class Log {
    public:
      Log();
      virtual ~Log();
      std::ostringstream& Get(LogLevel level = LOG_DEBUG);
    protected:
      std::ostringstream os;
    private:
      int l;
      Log(const Log&);
      Log& operator =(const Log&);
  };
  
  #ifndef MAX_LOG_LEVEL
  #define MAX_LOG_LEVEL Chimera::LOG_DEBUG
  #endif
  #ifndef LOG_FORMAT
  #define LOG_FORMAT __FILE__ << "(" << __LINE__ << ")" << ": "
  #endif
  #define DOLOG(level) if (level > MAX_LOG_LEVEL) ; else Chimera::Log().Get(level) << LOG_FORMAT
  #endif
  
  #define LOG DOLOG(Chimera::LOG_INFO)
  #define ERR DOLOG(Chimera::LOG_ERROR)
  #define DBG DOLOG(Chimera::LOG_DEBUG)
}
