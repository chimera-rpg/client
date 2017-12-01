#include "common/Cfg.hpp"
#include "common/Log.hpp"
#include <iostream>

namespace Chimera {
  Cfg::Cfg() {
  }
  
  Cfg::Cfg(std::string name) {
    readFromFilename(mName);
  }
  
  void Cfg::readFromFilename(std::string name) {
    mName = name;
    std::ifstream in(mName);
    if (in.is_open()) {
      readFromStream(in);
    }
  }
  
  void Cfg::readFromStream(std::ifstream &in) {
    std::string line;
    std::string key, value;
    std::istringstream sin;
  
    while (std::getline(in, line)) {
      std::string::iterator it;
      std::size_t pos, start;
  
      // strip leading white-space
      start = line.find_first_not_of("\t ");
      if (start != std::string::npos) {
        line = line.substr(start);
      }
      // if empty or starts with ';', continue to next line
      if (line.size() == 0 || line[0] == ';') {
        continue;
      }
      // get our key
      pos = line.find_first_of("\t\n ");
      key = line.substr(start, pos);
      if (pos != std::string::npos) {
        line = line.substr(pos);
      }
      // strip leading white-space
      start = line.find_first_not_of("\t ");
      if (start != std::string::npos) {
        line = line.substr(start);
      }
      value = line;
      set(key, value);
    }
  }
  
  const char* Cfg::getCString(const char *key) {
    auto it = mTable.find(key);
    if (it != mTable.end()) {
      return it->second.c_str();
    }
    return mNull;
  }
  std::string Cfg::get(const std::string &key) {
    auto it = mTable.find(key);
    if (it != mTable.end()) {
      return it->second;
    }
    return mNull;
  }
  int Cfg::getInt(std::string key) {
    auto it = mTable.find(key);
    if (it != mTable.end()) {
      return std::stoi(it->second);
    }
    return 0;
  }
  float Cfg::getFloat(std::string key) {
    auto it = mTable.find(key);
    if (it != mTable.end()) {
      return std::stof(it->second);
    }
    return 0.0f;
  }
  
  void Cfg::set(std::string key, std::string value) {
    mTable[key] = value;
  }
  void Cfg::setString(std::string key, std::string value) {
    mTable[key] = value;
  }
  void Cfg::setCString(const char *key, const char *value) {
    mTable[key] = value;
  }
  void Cfg::set(std::string key, int value) {
    mTable[key] = std::to_string(value);
  }
  void Cfg::set(std::string key, float value) {
    mTable[key] = std::to_string(value);
  }

}
