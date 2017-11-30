#pragma once
#include <string>
#include <fstream>
#include <unordered_map>

namespace Chimera { 
  class Cfg {
 
    public:
      Cfg();
      Cfg(std::string name);
  
      void readFromStream(std::ifstream &in);
      void readFromFilename(std::string name);
  
      std::string get(std::string key);
      int getInt(std::string key);
      float getFloat(std::string key);
      void setString(std::string key, std::string value);
      void set(std::string key, std::string value);
      void set(std::string key, int value);
      void set(std::string key, float value);

    private:
      std::string mName;
      std::unordered_map<std::string, std::string> mTable;
 
  };
}
