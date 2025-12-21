#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
#include <unordered_set>
class Vec2;

class Ex_9 : public Challenge
{
public:

	void Run1(ifstream& input) override;
	void AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out);
	void Run2(ifstream& input) override;
};

