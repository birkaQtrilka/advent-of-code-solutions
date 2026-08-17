#include "utils.h"
#include <chrono>
#include <thread>
#include "config.h"
#include <iostream>
#include <charconv>

void utils::DrawGrid(const vector<string>& grid, int delayMs) {
	static vector<string> prev;
	static bool first = true;
	static bool drawMode = false;
	if (first) {
		first = false;
		string drawModeKey = TryGetConfigKey("drawMode");
		if (drawModeKey == "1") drawMode = true;
		if (!drawMode) return;
		cout << "\033[?25l";   // hide cursor
		prev = grid;
	}
	if (!drawMode) return;

	// Move cursor to home
	cout << "\033[H";

	// Diff-based redraw
	for (int y = 0; y < (int)grid.size(); y++) {
		if (y >= prev.size() || grid[y] != prev[y]) {
			// Move cursor to row y, col 1
			cout << "\033[" << (y + 1) << ";1H";
			cout << grid[y];
		}
	}

	cout.flush();
	prev = grid;

	this_thread::sleep_for(chrono::milliseconds(delayMs));
}

void utils::DrawGrid(const vector<vector<bool>>& grid, int delayMs) {
	//static bool first = true;
	//static bool drawMode = false;
	//if (first) {
	//	first = false;
	//	string drawModeKey = TryGetConfigKey("drawMode");
	//	if (drawModeKey == "1") drawMode = true;
	//	if (!drawMode) return;
	//	cout << "\033[?25l";   // hide cursor
	//}
	//if (!drawMode) return;

	// Move cursor to home
	//cout << "\033[H";
	cout << "start" << endl;
	string frame;
	frame.reserve(grid.size() * (grid[0].size() + 1));

	for (const auto& row : grid) {
		for (bool v : row)
			frame.push_back(v ? '#' : '.');
		frame.push_back('\n');
	}
	cout << "\033[H" << frame;
	cout.flush();

}

void utils::CoutBoolArr(const vector<bool>& arr) {
	for (size_t i = 0; i < arr.size(); i++)
	{
		cout << (arr[i] ? '#' : '.');
	}
}

void utils::EnterPause() {
	static bool first = true;
	static bool drawMode = false;
	if (first) {
		first = false;
		string drawModeKey = TryGetConfigKey("drawMode");
		if (drawModeKey == "1") drawMode = true;
	}
	if (!drawMode) return;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string utils::TryGetConfigKey(const string& key) {
	std::string value = "";
	auto it = g_config.find(key);
	if (it != g_config.end())
		value = it->second;
	return value;
}

int utils::svtoi(string_view str) {
  if(str[0] == ' ') str = str.substr(1,1);
  int i;
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), i);
  return i; 
}

size_t utils::svtol(string_view str) {
  size_t i;
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), i);
  return i; 
}

int utils::cvtoi(const vector<char> str) {
  int i;
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), i);
  return i; 
}

void utils::checkNeighbours(
    const std::vector<std::string>& grid, 
    size_t x, 
    size_t y, 
    const std::function<void(size_t, size_t)>& callback
) {
    size_t cols = grid[0].size();
    size_t rows = grid.size();
    
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dy == 0 && dx == 0) continue;

            int ny = static_cast<int>(y) + dy;
            int nx = static_cast<int>(x) + dx;

            if (ny >= 0 && ny < static_cast<int>(rows) && 
                nx >= 0 && nx < static_cast<int>(cols)) {
                callback(static_cast<size_t>(ny), static_cast<size_t>(nx));
            }
        }
    }
}

size_t utils::popNext(size_t& offset, string_view str) {
  size_t space_pos = str.find(' ', offset);
  size_t count = (space_pos == string_view::npos) ? (str.size() - offset) : (space_pos - offset);
  
  size_t num = utils::svtol(str.substr(offset, count));
  
  offset = (space_pos == string_view::npos) ? str.size() : space_pos + 1;
  return num;
}