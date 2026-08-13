#pragma once
#include "../Challenge.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
class Ex_25_6 : public Challenge
{
public:

	void Run1(ifstream& input) override;
	void Run11(istream& input);
	void Run12(istream& input);
	vector<vector<int>> AlignVectors(const vector<vector<int>>& input, int chunkSize);
	void Run2(ifstream& input) override;
};

