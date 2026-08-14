#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using namespace std;

namespace utils {
	void DrawGrid(const vector<string>& grid, int delayMs);
	void DrawGrid(const vector<vector<bool>>& grid, int delayMs);
	void EnterPause();
	string TryGetConfigKey(const string& key);
  int svtoi(string_view str);
  int cvtoi(vector<char> str);
  void checkNeighbours(const std::vector<std::string> &grid, size_t x, size_t y, const std::function<void(size_t, size_t)> &callback);
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
