//	Part One – Count how many times the tachyon beam splits
//	
//	A tachyon beam starts at S and moves downward through a grid.
//	Empty space (.) lets the beam pass. A splitter (^) stops the incoming beam
//	and creates two new beams that continue downward from the immediate left and right.
//	Beams may overlap and continue independently.
//	
//	--> How many total beam splits occur as all beams travel through the manifold?
//	
//	Part Two – Count all resulting quantum timelines
//	
//	A quantum tachyon manifold sends a single particle through the grid.
//	At each splitter, the particle takes both paths—one timeline goes left, the
//	other goes right. Time itself splits, and both timelines continue independently.
//	
//	--> After the particle completes all possible journeys, how many distinct timelines exist?


#include "Ex_7.h"
#include <stack>
#include "utils.h"

struct Point {
	int x = 0;
	int y = 0;
};

void Ex_7::Run1(ifstream& input)
{
	vector<string> grid;
	string line;
	while (getline(input, line)) {
		grid.push_back(line);
	}
	int start = grid[0].find('S');
	Point size = {grid[0].size(), grid.size()};
	stack<Point> ops;
	ops.push({ start, 1});
	int splitCount = 0;
	
	utils::EnterPause();

	while (!ops.empty()) {
		Point i = ops.top();
		ops.pop();
		grid[i.y][i.x] = '|';
		utils::DrawGrid(grid, 1);

		if (i.y + 1 >= size.y) continue;
		char down = grid[i.y + 1][i.x];
		if (down == '^') {
			bool hasSplit = false;
			Point left = { i.x - 1, i.y + 1 };
			if (i.x - 1 > -1 && grid[left.y][left.x] == '.') {
				ops.push(left);
				hasSplit = true;
			}
			Point right = { i.x + 1, i.y + 1 };
			if (i.x + 1 < size.x && grid[right.y][right.x] == '.') {
				ops.push(right);
				hasSplit = true;
			}
			splitCount+= hasSplit;

		}
		else if (down == '.') {
			ops.push({ i.x , i.y + 1 });
		}
	}
	cout << "Ex_7: " << splitCount << endl;
}

long long Ex_7::Dfs(int x, int y, const vector<string>& grid,
	vector<vector<long long>>& memo)
{
	int H = grid.size();
	int W = grid[0].size();

	if (y == H - 1)
		return 1;
	// if count already calculated, don't repeat dfs
	if (memo[y][x] != -1)
		return memo[y][x];

	long long result = 0;
	char down = grid[y + 1][x];

	if (down == '.')
	{
		result = Dfs(x, y + 1, grid, memo);
	}
	else if (down == '^')
	{
		result = 0;
		if (x > 0)
			result += Dfs(x - 1, y + 1, grid, memo);
		if (x < W - 1)
			result += Dfs(x + 1, y + 1, grid, memo);
	}

	memo[y][x] = result;
	return result;
}

void Ex_7::Run2(ifstream& input)
{
	vector<string> grid;
	string line;

	while (getline(input, line))
		grid.push_back(line);

	int start = grid[0].find('S');
	vector<vector<long long>> memo(grid.size(),
		vector<long long>(grid[0].size(), -1));

	long long timelines = Dfs(start, 0, grid, memo);

	cout << "Ex_7 Part 2: " << timelines << endl;
}


