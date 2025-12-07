#include "Registry.h"
#include <vector>
#include <iostream>

static std::vector<ChallengeData> registry;

void Registry::registerClass(ChallengeData challenge) {
  registry.push_back(challenge);
}

void Registry::instantiateAndRun() {
  for (int i = registry.size() - 1; i > -1; --i) {
    std::unique_ptr<Challenge> obj = registry[i].creator();
    obj->Run(registry[i].inputName);
    std::cout << std::endl << std::endl;
  }
}

void Registry::instantiateAndRunLast()
{
  int i = registry.size() - 1;
  std::unique_ptr<Challenge> obj = registry[i].creator();
  obj->Run(registry[i].inputName);
}
