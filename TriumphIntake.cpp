#include "Registry.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "config.h"

extern void registerClasses();

std::unordered_map<std::string, std::string> loadConfig(const std::string& filename)
{
  std::unordered_map<std::string, std::string> config;
  std::ifstream file(filename);

  if (!file.is_open())
  {
    std::cerr << "Could not open config file: " << filename << std::endl;
    return config;
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty()) continue;  // skip empty lines

    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
    {
      std::cerr << "Invalid config line (missing comma): " << line << std::endl;
      continue;
    }

    std::string key = line.substr(0, commaPos);
    std::string value = line.substr(commaPos + 1);

    // trim spaces (optional)
    auto trim = [](std::string& s) {
      while (!s.empty() && isspace(s.front())) s.erase(s.begin());
      while (!s.empty() && isspace(s.back())) s.pop_back();
      };

    trim(key);
    trim(value);

    config[key] = value;
  }

  return config;
}

int main()
{
  registerClasses();
  g_config = loadConfig("myConfig.txt");

  std::string filePtr = "";
  auto it = g_config.find("testFile");
  if ( it != g_config.end())
    filePtr = it->second; // second is value

  Registry::instantiateAndRunLastOrGivenFile(filePtr);
  return 0;
}
