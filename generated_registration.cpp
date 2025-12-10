#include "Registry.h"
#include "./Exercices/Ex_1.h";
#include "./Exercices/Ex_2.h";
#include "./Exercices/Ex_3.h";
#include "./Exercices/Ex_4.h";
#include "./Exercices/Ex_5.h";
#include "./Exercices/Ex_6.h";
#include "./Exercices/Ex_7.h";
#include "./Exercices/Ex_8.h";
#include "./Exercices/Ex_9.h";

void registerClasses() {
	REGISTER_DERIVED_CLASS(Ex_1, "Inputs/Ex_1_input.txt");
	REGISTER_DERIVED_CLASS(Ex_2, "Inputs/Ex_2_input.txt");
	REGISTER_DERIVED_CLASS(Ex_3, "Inputs/Ex_3_input.txt");
	REGISTER_DERIVED_CLASS(Ex_4, "Inputs/Ex_4_input.txt");
	REGISTER_DERIVED_CLASS(Ex_5, "Inputs/Ex_5_input.txt");
	REGISTER_DERIVED_CLASS(Ex_6, "Inputs/Ex_6_input.txt");
	REGISTER_DERIVED_CLASS(Ex_7, "Inputs/Ex_7_input.txt");
	REGISTER_DERIVED_CLASS(Ex_8, "Inputs/Ex_8_input.txt");
	REGISTER_DERIVED_CLASS(Ex_9, "Inputs/Ex_9_input.txt");

}
