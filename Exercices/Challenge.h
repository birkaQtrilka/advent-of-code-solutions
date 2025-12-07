#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Challenge
{
public:
	virtual void Run(const string& inputName);
	virtual void Run1(ifstream& input) = 0;
	virtual void Run2(ifstream& input) = 0;
};

