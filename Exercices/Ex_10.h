#pragma once
#include "Challenge.h"
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <string>
#include <functional>
#include <cstdint>
using namespace std;

struct Combination {
	int start;
	int depth;
	uint32_t result;
};

struct Button {
	int maxPresses = 0;
	vector<int> affects;
};

struct VecN {
	std::vector<int> data;

	bool operator==(const VecN& other) const {
		return data == other.data;
	}

	VecN(int size) {
		data = vector<int>(size, 0);
	}

	int euclideanDistance(const VecN& other) const {

		int sum = 0;
		for (size_t i = 0; i < data.size(); ++i) {
			int diff = data[i] - other.data[i];
			sum += diff * diff;
		}
		return sum;
	}

	int manhattanDistance(const VecN& other) const {

		int sum = 0;
		for (size_t i = 0; i < data.size(); ++i) {
			sum += std::abs(data[i] - other.data[i]);
		}
		return sum;
	}
};

struct VecNHash {
	size_t operator()(const VecN& v) const noexcept {
		size_t seed = v.data.size();
		for (int x : v.data) {
			seed ^= std::hash<int>{}(x)+0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};
struct Combination2 {
	int distanceToStart = 0;
	VecN pos;
};

class Ex_10 : public Challenge
{
public:

	void Toggle(uint32_t& bits, int i);

	string ToBitString(uint32_t value);

	void Run1(ifstream& input) override;
	int AnalyzeLine(const string& line);
	int AnalyzeLine2(const string& line);
	void Run2(ifstream& input) override;
	void ForEachContent(const string& line, const string& s, const string& e, const function<void(const string&)>& callback);
	void GetNumber(string& content, const function<void(int)>& callback);
};

