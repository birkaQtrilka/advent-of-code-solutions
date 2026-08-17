#include "Registry.h"

#include ".\Exercices\2023\Ex_23_1.h"
#include ".\Exercices\2023\Ex_23_2.h"
#include ".\Exercices\2023\Ex_23_3.h"
#include ".\Exercices\2023\Ex_23_4.h"
#include ".\Exercices\2023\Ex_23_5.h"
#include ".\Exercices\2023\Ex_23_6.h"

void registerClasses() {
	REGISTER_DERIVED_CLASS(Ex_23_1, "Inputs/Ex_23_1_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_2, "Inputs/Ex_23_2_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_3, "Inputs/Ex_23_3_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_4, "Inputs/Ex_23_4_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_5, "Inputs/Ex_23_5_input.txt");
	REGISTER_DERIVED_CLASS(Ex_23_6, "Inputs/Ex_23_6_input.txt");
}
