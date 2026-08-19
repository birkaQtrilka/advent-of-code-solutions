#include "Registry.h"

#include ".\Exercices\2022\Ex_22_1.h"
#include ".\Exercices\2022\Ex_22_2.h"

void registerClasses() {
	REGISTER_DERIVED_CLASS(Ex_22_1, "Inputs/Ex_22_1_input.txt");
	REGISTER_DERIVED_CLASS(Ex_22_2, "Inputs/Ex_22_2_input.txt");
}
