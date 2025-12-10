#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
class Vec2;

class Ex_9 : public Challenge
{
public:

	void Run1(ifstream& input) override;
	void Run2(ifstream& input) override;
	void AvailableBounds(int x, int y, int s_x, int s_y, vector<Vec2>& bounds);
	bool IsInside(const vector<Vec2>& poly, Vec2 p);
	Vec2 GetFirstPointInsideLoop(vector<Vec2>& bounds, const vector<Vec2>& other, Vec2 corner, int s_x, int s_y);
	void Connect(vector<vector<bool>>& grid, Vec2 a, Vec2 b);
};

