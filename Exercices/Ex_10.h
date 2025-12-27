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

struct Combination2 {
	int start;
	//uint32_t affectedButtons;
	int presses;
	vector<int> result;
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

