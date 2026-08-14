#include "Registry.h"

#include ".\Exercices\2023\Ex_23_1.h"
#include ".\Exercices\2023\Ex_23_2.h"
#include ".\Exercices\2023\Ex_23_3.h"

void registerClasses() {
	REGISTER_DERIVED_CLASS(Ex_23_1, "Inputs/Ex_23_1_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_2, "Inputs/Ex_23_2_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_3, "Inputs/Ex_23_3_input.txt");
}
