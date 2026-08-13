#pragma once
#include "../Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>

class Ex_23_1 : public Challenge
{
public:

	void Run1(ifstream& input) override;
  char match(const std::array<string, 10> &arr, std::string_view str);
  void Run2(ifstream &input) override;
};
