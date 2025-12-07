#include "utils.h"
#include <chrono>
#include <thread>
#include "config.h"
#include <iostream>

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