#include "Ex_9.h"
#include <stack>
#include <algorithm>
#include <array>
#include "../utils.h"
struct Vec2 {
  int x;
  int y;
};
void Ex_9::Run1(ifstream& input)
{
  return;
  vector<Vec2> positions;

  string line;
  while (getline(input, line)) {
    int x, y;
    sscanf_s(line.c_str(), "%d,%d", &x, &y);
    positions.push_back({ x, y });
  }
  long long max = -1;

  for (size_t i = 0; i < positions.size() - 1; i++)
  {
    for (size_t j = i + 1; j < positions.size(); j++)
    {
      Vec2 a = positions[i];
      Vec2 b = positions[j];
      int w = abs(a.x - b.x)+1;
      int h = abs(a.y - b.y)+1;
      long long area = 1LL * w * h;
      if (area > max) max = area;
    }
  }

  cout << "Ex_9: " << max << endl;

}

void Ex_9::Run2(ifstream& input)
{
  vector<Vec2> positions;
  vector<Vec2> greensLookup;
  
  string line;

  Vec2 currMax = {0,0};
  while (getline(input, line)) {
    int x, y;
    sscanf_s(line.c_str(), "%d,%d", &x, &y);
    positions.push_back({ x, y });
    currMax.x = max(currMax.x, x);
    currMax.y = max(currMax.y, y);
  }
  currMax.x++;
  currMax.y++;
  // create grid
  vector<vector<bool>> grid;
  grid.assign(currMax.y, vector<bool>(currMax.x));
  utils::EnterPause();
  // connect edges
  for (size_t p_i = 1; p_i < positions.size(); p_i++) { // can offset to save memory
    Vec2 a = positions[p_i - 1];
    Vec2 b = positions[p_i];
    
    Connect(grid, a, b);
  }
  Connect(grid, positions[0], positions[positions.size()-1]);
  utils::DrawGrid(grid, 100);

  return;
  // bfs flood fill
  stack<Vec2> stack;
  vector<Vec2> bounds(4);
  
  stack.push(GetFirstPointInsideLoop(bounds, positions, positions[0], currMax.x, currMax.y));

  while (!stack.empty()) {
    Vec2 current = stack.top();
    stack.pop();
    if (grid[current.y][current.x]) continue;
    grid[current.y][current.x] = true;
    //utils::DrawGrid(grid, 200);
    // move up down, top, right
    bounds.clear();
    AvailableBounds(current.x, current.y, currMax.x, currMax.y, bounds);

    for (auto& b : bounds) {
      if(!grid[b.y][b.x]) stack.push(b);
    }
  }
  long long max = -1;
  return;
  for (size_t i = 0; i < positions.size() - 1; i++) {
    for (size_t j = i + 1; j < positions.size(); j++) {
      Vec2 a = positions[i];
      Vec2 b = positions[j];
      // check if other corners are not green
      Vec2 green_check_a = { a.x, b.y };
      Vec2 green_check_b = { b.x, a.y };
      if (!grid[green_check_a.y][green_check_a.x] || !grid[green_check_b.y][green_check_b.x]) continue;

      int w = abs(a.x - b.x) + 1;
      int h = abs(a.y - b.y) + 1;
      long long area = 1LL * w * h;
      if (area > max) max = area;
    }
  }

  cout << "Ex_9: " << max << endl;
}

void Ex_9::Connect(vector<vector<bool>>& grid, Vec2 a, Vec2 b) {
  int w = b.x - a.x;
  int h = b.y - a.y;
  if (w == 0) {
    int sign = h < 0 ? -1 : 1;
    int abs_h = h * sign;
    for (int i = 1; i < abs_h; i++) {
      grid[a.y + i * sign][a.x] = true;
      //utils::DrawGrid(grid, 200);
    }
  }
  else {
    int sign = w < 0 ? -1 : 1;
    int abs_w = w * sign;
    for (int i = 1; i < abs_w; i++) {
      grid[a.y][a.x + i * sign] = true;
      //utils::DrawGrid(grid, 200);
    }
  }
}

void Ex_9::AvailableBounds(int x, int y, int s_x, int s_y, vector<Vec2>& bounds) {
  if (x - 1 > -1) bounds.push_back({ x - 1, y });
  if (x + 1 < s_x) bounds.push_back({ x + 1, y });
  if (y - 1 > -1) bounds.push_back({ x, y - 1 });
  if (y + 1 < s_y) bounds.push_back({ x, y + 1 });

}

bool Ex_9::IsInside(const vector<Vec2>& poly, Vec2 p) {
  bool inside = false;
  int n = poly.size();

  for (int i = 0, j = n - 1; i < n; j = i++) {

    // Check if the line between poly[i]..poly[j] intersects the ray
    bool intersect = ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
      (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y) /
        (poly[j].y - poly[i].y) + poly[i].x);

    if (intersect)
      inside = !inside;
  }

  return inside;
}

Vec2 Ex_9::GetFirstPointInsideLoop(vector<Vec2>& bounds, const vector<Vec2>& other, Vec2 corner, int s_x, int s_y) {
  int x = corner.x;
  int y = corner.y;
  // checking diagonals
  if (y + 1 < s_y && x + 1 < s_x) bounds.push_back({ x + 1, y + 1 });
  if (y - 1 > -1 && x - 1 > -1) bounds.push_back({ x - 1, y - 1 });
  if (x + 1 < s_x && y - 1 > -1) bounds.push_back({ x + 1, y - 1 });
  if (x - 1 > -1 && y + 1 < s_y) bounds.push_back({ x - 1, y + 1 });

  for (auto& b : bounds)
  {
    if (IsInside(other, b)) return b;
  }
  return { -1,-1 };
}

