#pragma once
#include <vector>
#include <string>

using namespace std;
namespace utils {
	void DrawGrid(const vector<string>& grid, int delayMs);
	void EnterPause();
	string TryGetConfigKey(const string& key);
}

