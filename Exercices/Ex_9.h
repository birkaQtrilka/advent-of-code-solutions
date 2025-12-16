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
	void Connect(unordered_set<long long>& grid, Vec2 a, Vec2 b);
	bool IsInside(const vector<Vec2>& poly, Vec2 p);
	void AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out);
	Vec2 GetFirstPointInsideLoop(vector<Vec2>& tmp, const vector<Vec2>& poly, Vec2 corner, int maxX, int maxY);
	void Run2(ifstream& input) override;
	void WriteFilledSVG(const unordered_set<long long>& filled, int maxX, int maxY, int scale, string filename);
	void WriteSVG(const vector<Vec2>& positions, const string& filename);
};

