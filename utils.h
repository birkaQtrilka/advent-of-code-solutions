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
  size_t svtol(string_view str);
  int cvtoi(vector<char> str);
  void checkNeighbours(const std::vector<std::string> &grid, size_t x, size_t y, const std::function<void(size_t, size_t)> &callback);
  size_t popNext(size_t &offset, string_view str);
  string_view popNextStr(size_t &offset, std::string_view str);
  void CoutBoolArr(const vector<bool> &arr);
  template<typename... Args>
  void println(Args... args) {
      (std::cout << ... << args) << '\n';
  }

  template<typename... Args>
  void println_d(string& delim, Args... args) {
      ((std::cout << args << delim), ...) << '\n';
  }

  inline bool isDigit(unsigned char c) {
    return std::isdigit(c);
}

// Main function with customizable predicate
template<typename Predicate = decltype(isDigit)>
std::string_view popNextStr(size_t& offset, std::string_view str, Predicate pred = isDigit) {
    // Find next space
    size_t space_pos = str.find(' ', offset);
    
    // Extract the number portion
    size_t count = (space_pos == std::string_view::npos) 
             ? (str.size() - offset) 
             : (space_pos - offset);
    
    // Convert to number
    std::string_view result = str.substr(offset, count);
    
    // Update offset to the next valid character after the space
    if (space_pos == std::string_view::npos) {
        offset = str.size();
    } else {
        // Start searching after the space
        auto it = std::find_if(str.begin() + space_pos + 1, str.end(), 
            [&pred](unsigned char c) { return pred(c); });
        offset = (it == str.end()) ? str.size() : (it - str.begin());
    }
    
    return result;
}

// Overload for default predicate (no need to specify)
inline std::string_view popNextStr(size_t& offset, std::string_view str) {
    return popNextStr(offset, str, isDigit);
}
}
