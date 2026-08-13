#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>

struct Point {
	int x = 0;
	int y = 0;
};

class Ex_25_4 : public Challenge
{
public:
	void Run1(ifstream& input) override;
	void Run2(ifstream& input) override;
	void AvailableBounds(int x, int y, int s, vector<Point>& bounds);
};

