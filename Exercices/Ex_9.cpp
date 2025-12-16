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
      int w = abs(a.x - b.x) + 1;
      int h = abs(a.y - b.y) + 1;
      long long area = 1LL * w * h;
      if (area > max) max = area;
    }
  }

  cout << "Ex_9: " << max << endl;

}

inline long long key(int x, int y) {
  return ((long long)y << 32) | (unsigned long long)x;
}

inline bool get(const unordered_set<long long>& grid, int x, int y) {
  return grid.count(key(x, y));
}

inline void setp(unordered_set<long long>& grid, int x, int y) {
  grid.insert(key(x, y));
}

//--------------------------------------------
// CONNECT EDGES (sparse version)
//--------------------------------------------
void Ex_9::Connect(unordered_set<long long>& grid, Vec2 a, Vec2 b)
{
  if (a.x == b.x) {
    int dy = (b.y > a.y) ? 1 : -1;
    for (int y = a.y; y != b.y; y += dy) {
      setp(grid, a.x, y);
    }
    setp(grid, b.x, b.y);
  }
  else {
    int dx = (b.x > a.x) ? 1 : -1;
    for (int x = a.x; x != b.x; x += dx) {
      setp(grid, x, a.y);
    }
    setp(grid, b.x, b.y);
  }
}

bool Ex_9::IsInside(const vector<Vec2>& poly, Vec2 p)
{
  bool inside = false;
  int n = poly.size();

  for (int i = 0, j = n - 1; i < n; j = i++)
  {
    bool intersect =
      ((poly[i].y > p.y) != (poly[j].y > p.y)) &&
      (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y)
        / double(poly[j].y - poly[i].y) + poly[i].x);

    if (intersect) inside = !inside;
  }
  return inside;
}

void Ex_9::AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out)
{
  out.clear();
  if (x > 0)         out.push_back({ x - 1, y });
  if (x + 1 < maxX)  out.push_back({ x + 1, y });
  if (y > 0)         out.push_back({ x, y - 1 });
  if (y + 1 < maxY)  out.push_back({ x, y + 1 });
}

Vec2 Ex_9::GetFirstPointInsideLoop(vector<Vec2>& tmp,
  const vector<Vec2>& poly,
  Vec2 corner, int maxX, int maxY)
{
  tmp.clear();

  int x = corner.x;
  int y = corner.y;

  // check diagonals
  if (x + 1 < maxX && y + 1 < maxY) tmp.push_back({ x + 1, y + 1 });
  if (x > 0 && y > 0)               tmp.push_back({ x - 1, y - 1 });
  if (x + 1 < maxX && y > 0)        tmp.push_back({ x + 1, y - 1 });
  if (x > 0 && y + 1 < maxY)        tmp.push_back({ x - 1, y + 1 });

  for (auto& p : tmp)
    if (IsInside(poly, p)) return p;

  return { -1, -1 };
}

void Ex_9::Run2(ifstream& input)
{
  vector<Vec2> positions;
  string line;

  int maxX = 0, maxY = 0;

  // read input
  while (getline(input, line)) {
    int x, y;
    sscanf_s(line.c_str(), "%d,%d", &x, &y);

    positions.push_back({ x, y });
  }
  unordered_set<long long> grid;
  for (size_t i = 1; i < positions.size(); i++) {
    Connect(grid, positions[i - 1], positions[i]);
  }
  Connect(grid, positions[0], positions[positions.size() - 1]);
  // bfs fill


  long long best = -1;

  for (size_t i = 0; i < positions.size(); ++i)
  {
    for (size_t j = i + 1; j < positions.size(); ++j)
    {
      Vec2 a = positions[i];
      Vec2 b = positions[j];

      Vec2 c = { a.x, b.y };
      Vec2 d = { b.x, a.y };


      long long area =
        1LL * (abs(a.x - b.x) + 1) *
        (abs(a.y - b.y) + 1);

      best = max(best, area);
    }
  }

  cout << "Ex_9: " << best << endl;
}
void Ex_9::WriteFilledSVG(const unordered_set<long long>& filled,
  int maxX, int maxY, int scale, string filename)
{
  ofstream out(filename);
  out << "<svg xmlns='http://www.w3.org/2000/svg' fill='black' stroke='none'>";

  for (auto& cell : filled)
  {
    int x = cell & 0xffffffff;
    int y = cell >> 32;
    out << "<rect x='" << x * scale
      << "' y='" << y * scale
      << "' width='" << scale
      << "' height='" << scale << "' />\n";
  }

  out << "</svg>";
}
void Ex_9::WriteSVG(const vector<Vec2>& positions, const string& filename) {
  ofstream out(filename);
  out << "<svg xmlns='http://www.w3.org/2000/svg' "
    "stroke='black' fill='none'>\n";

  out << "<polyline points='";
  for (auto& p : positions)
    out << p.x << "," << p.y << " ";
  out << positions[0].x << "," << positions[0].y;  // close shape
  out << "' stroke='black' stroke-width='1'/>\n";

  out << "</svg>";
}