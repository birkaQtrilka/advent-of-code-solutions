
/*Part One – Count accessible rolls of paper

You are given a grid where @ marks rolls of paper.
A roll is considered accessible if fewer than four other rolls appear in the eight
adjacent cells around it (including diagonals).

--> How many rolls of paper on the grid are accessible by a forklift?

Part Two – Repeatedly remove accessible rolls

Once an accessible roll is removed, the grid changes and new rolls may become
accessible. This process repeats: remove all currently accessible rolls, update
the grid, and continue until no rolls remain accessible.

--> How many total rolls of paper can be removed through this repeated process?
*/


#include "Ex_4.h"

void Ex_4::Run1(ifstream& input)
{
	return;
	vector<string> grid;
	string line;
	while (getline(input, line)) {
		if (line.empty()) continue;
		grid.push_back(line);
	}
	int width = grid[0].size();
	vector<Point> availableBounds;

	int count = 0;
	for (size_t y = 0; y < width; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (grid[y][x] != '@') continue;
			availableBounds.clear();
			AvailableBounds(x, y, width, availableBounds);
			int paperRollCount = 0;
			for (auto& b : availableBounds) {
				paperRollCount+= grid[b.y][b.x] == '@';
			}
			count += paperRollCount < 4;
		}
	}
	cout << "Ex_4: " << count << endl;
}

void Ex_4::AvailableBounds(int x, int y, int s, vector<Point>& bounds) {
	if (x - 1 > -1) bounds.push_back({x - 1, y});
	if (x + 1 < s) bounds.push_back({x + 1, y});
	if (y - 1 > -1) bounds.push_back({x, y - 1 });
	if (y + 1 < s) bounds.push_back({ x, y + 1 });

	if(y + 1 < s && x + 1 < s) bounds.push_back({ x + 1, y + 1 });
	if(y - 1 > -1 && x - 1 > -1) bounds.push_back({ x - 1, y - 1 });
	if(x + 1 < s && y - 1 > -1) bounds.push_back({ x + 1, y - 1 });
	if(x - 1 > -1 && y + 1 < s) bounds.push_back({ x - 1, y + 1 });
}

void Ex_4::Run2(ifstream& input)
{
	vector<string> grid;
	string line;
	while (getline(input, line)) {
		if (line.empty()) continue;
		grid.push_back(line);

	}
	int width = grid[0].size();
	vector<Point> availableBounds;
	vector<Point> toBeRemoved;
	int count = 0;
	do {
		for (Point& p : toBeRemoved) {
			grid[p.y][p.x] = '.';
		}
		toBeRemoved.clear();
		for (int y = 0; y < width; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (grid[y][x] != '@') {
					continue;
				}
				availableBounds.clear();
				AvailableBounds(x, y, width, availableBounds);
				int paperRollCount = 0;
				for (auto& b : availableBounds) {
					paperRollCount += grid[b.y][b.x] == '@';
				}
				if (paperRollCount < 4) {
					toBeRemoved.push_back({ x, y });
					count++;
				}
			}
		}

	} while (toBeRemoved.size() != 0);
	
	cout << "Ex_4: " << count << endl;
}
