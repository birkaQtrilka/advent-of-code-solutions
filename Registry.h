#ifndef REGISTRY_H
#define REGISTRY_H

#include <memory>
#include "./Exercices/Challenge.h"
#include <string>

struct ChallengeData {
    std::unique_ptr<Challenge>(*creator)();
    string inputName;
};

class Registry {
public:
    static void registerClass(ChallengeData data);
    static void instantiateAndRun();
    static void instantiateAndRunLast(const std::string& file = "");
};

#define REGISTER_DERIVED_CLASS(Derived, FileName) \
    Registry::registerClass({[]() -> std::unique_ptr<Challenge> { return std::make_unique<Derived>(); }, FileName});

#endif // REGISTRY_H