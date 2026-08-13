#include "Registry.h"

#include "./Exercices/2025/Ex_25_1.h"
#include "./Exercices/2025/Ex_25_2.h"
#include "./Exercices/2025/Ex_25_3.h"
#include "./Exercices/2025/Ex_25_4.h"
#include "./Exercices/2025/Ex_25_5.h"
#include "./Exercices/2025/Ex_25_6.h"
#include "./Exercices/2025/Ex_25_7.h"
#include "./Exercices/2025/Ex_25_8.h"
#include "./Exercices/2025/Ex_25_9.h"
#include "./Exercices/2025/Ex_25_10.h"

void registerClasses() {
	REGISTER_DERIVED_CLASS(Ex_25_1, "Inputs/Ex_25_1_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_2, "Inputs/Ex_25_2_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_3, "Inputs/Ex_25_3_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_4, "Inputs/Ex_25_4_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_5, "Inputs/Ex_25_5_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_6, "Inputs/Ex_25_6_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_7, "Inputs/Ex_25_7_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_8, "Inputs/Ex_25_8_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_9, "Inputs/Ex_25_9_input.txt");
	REGISTER_DERIVED_CLASS(Ex_25_10, "Inputs/Ex_25_10_input.txt");
}
