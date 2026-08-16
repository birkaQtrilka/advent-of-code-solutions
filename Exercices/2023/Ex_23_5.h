#pragma once
#include "../Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>

class Ex_23_5 : public Challenge
{
public:

	void Run1(ifstream& input) override;
	void Run2(ifstream& input) override;
  void MySolution(ifstream &input);
  void AI(ifstream &input);
};
