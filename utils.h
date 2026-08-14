#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace utils {
	void DrawGrid(const vector<string>& grid, int delayMs);
	void DrawGrid(const vector<vector<bool>>& grid, int delayMs);
	void EnterPause();
	string TryGetConfigKey(const string& key);
  int svtoi(string_view str);
  int cvtoi(vector<char> str);
  void CoutBoolArr(const vector<bool> &arr);
  template<typename... Args>
  void println(Args... args) {
      (std::cout << ... << args) << '\n';
  }

  template<typename... Args>
  void println_d(string& delim, Args... args) {
      ((std::cout << args << delim), ...) << '\n';
  }
}
