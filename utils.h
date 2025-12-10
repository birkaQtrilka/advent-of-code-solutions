#pragma once
#include <vector>
#include <string>

using namespace std;
namespace utils {
	void DrawGrid(const vector<string>& grid, int delayMs);
	void DrawGrid(const vector<vector<bool>>& grid, int delayMs);
	void EnterPause();
	string TryGetConfigKey(const string& key);
	void CoutBoolArr(const vector<bool>& arr);
}

