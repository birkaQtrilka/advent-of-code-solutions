#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
#include <unordered_set>
class Vec2;
class Rect;

class Ex_9 : public Challenge
{
public:

	void Run1(ifstream& input) override;
	void AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out);
	void Run2(ifstream& input) override;
	bool IsRectInPolygon(Rect r, const std::vector<Vec2>& poly);
	bool OnSegment(Vec2 p, Vec2 a, Vec2 b);
	void IsPointInPolygon(Vec2 p, Vec2 a, Vec2 b, bool& inside);

};

