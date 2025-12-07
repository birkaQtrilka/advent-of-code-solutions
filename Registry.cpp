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

void Registry::instantiateAndRunLast(const std::string& file)
{
  int i;

  auto it = std::find_if(registry.begin(), registry.end(),
    [file](const ChallengeData& x) {
      return x.inputName == file;
    }
  );

  if (it != registry.end()) {
    i = std::distance(registry.begin(), it);
  }
  else {
    i = registry.size() - 1;
  }

  // Now instantiate and run the correct challenge
  std::unique_ptr<Challenge> obj = registry[i].creator();
  obj->Run(registry[i].inputName);
}

