#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
#include <array>

struct Vec2 {
	int x = 0;
	int y = 0;
};

struct Rect {
	Vec2 min;
	Vec2 max;
	long long area;

	bool operator<(const Rect& other) const {
		return area < other.area;
	}
};

class PointData {
public:
	bool inside = false;
	bool onSegment = false;
	Vec2 p;
	Vec2 other;
	PointData() = default;
	PointData(Vec2 point, Vec2 otherP) : p(point), other(otherP) {}
};

class Ex_9 : public Challenge
{
public:
	array<PointData, 4> points;

	void Run1(ifstream& input) override;
	void AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out);
	bool SegmentsIntersect(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4);
	void Run2(ifstream& input) override;
	bool IsRectInPolygon(Rect r, const std::vector<Vec2>& poly);
	bool OnSegment(Vec2 p, Vec2 a, Vec2 b);
	void IsPointInPolygon(Vec2 p, Vec2 a, Vec2 b, bool& inside);

};

