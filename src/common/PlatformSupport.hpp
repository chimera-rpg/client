#pragma once
#define UNIX 0
#define MACOS 1
#define WINDOWS 2
#if defined(_WIN32)
#define PLATFORM WINDOWS
#elif defined(__APPLE__)
#define PLATFORM MACOS
#elif defined(unix) || defined(__unix__) || defined(__unix)
#define PLATFORM UNIX
#endif

#if PLATFORM == WINDOWS
#define DLL_EXT ".dll"
#define OS_SLASH "\\"
#include <windows.h>
  std::wstring s2mb(const std::string& s) {
    int slength = (int)s.length() + 1;
    int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t *buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
  }
  std::wstring s2ws(const std::string& s) {
    std::wstring stemp;
#ifdef UNICODE
    stemp = s2mb(s);
#else
    stemp = s;
#endif
    return stemp;
  }

  std::string GetLastErrorAsString() {
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
      return std::string();
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    std::string message(messageBuffer, size);

    LocalFree(messageBuffer);

    return message;
  }
#elif PLATFORM == MACOS
#define DLL_EXT ".dylib"
#define OS_SLASH "/"
#elif PLATFORM == UNIX
#define DLL_EXT ".so"
#define OS_SLASH "/"
#endif

#ifndef DLL_EXT
#error "No dynamic library extension defined for this operating system. Check ModuleSupport.hpp, PlatformSupport, and Client.cpp for adding OS support."
#endif
