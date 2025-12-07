#include "Registry.h"
extern void registerClasses();

int main()
{
    registerClasses();
    Registry::instantiateAndRunLast();
    return 0;
}