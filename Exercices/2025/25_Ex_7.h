#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>



class Ex_7 : public Challenge
{
public:
	void Run1(ifstream& input) override;
	long long Dfs(int x, int y, const vector<string>& grid, vector<vector<long long>>& memo);
	void Run2(ifstream& input) override;
};

