#include "Ex_9.h"
#include <stack>
#include <algorithm>
#include <array>
#include "../utils.h"
#include <queue>

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

void Ex_9::AvailableBounds(int x, int y, int maxX, int maxY, vector<Vec2>& out)
{
  out.clear();
  if (x > 0)         out.push_back({ x - 1, y });
  if (x + 1 < maxX)  out.push_back({ x + 1, y });
  if (y > 0)         out.push_back({ x, y - 1 });
  if (y + 1 < maxY)  out.push_back({ x, y + 1 });
}

struct Rect {
  Vec2 min;
  Vec2 max;
	long long area;

  bool operator<(const Rect& other) const {
    return area < other.area;
  }
};

void Ex_9::Run2(ifstream& input)
{
  vector<Vec2> positions;
  string line;

  while (getline(input, line)) {
    int x, y;
    sscanf_s(line.c_str(), "%d,%d", &x, &y);

    positions.push_back({ x, y });
  }
  // three for loops
	// loop 1-2 - go through all pairs of points
	// make rectangle
  // 
	// loop 3 - check if any other point is inside the rectangle formed by the pair

  

  std::priority_queue<Rect> pq;

	long long smallestArea = INT_MAX;

  for (size_t i = 0; i < positions.size(); ++i)
  {
    for (size_t j = i + 1; j < positions.size(); ++j)
    {
      Vec2 a = positions[i];
      Vec2 b = positions[j];
      int w = abs(a.x - b.x) + 1;
      int h = abs(a.y - b.y) + 1;

			Vec2 min = { std::min(a.x, b.x), std::min(a.y, b.y) };
			Vec2 max = { std::max(a.x, b.x), std::max(a.y, b.y) };
      long long area = 1LL * w * h;

      pq.push({min, max, area});


    }
  }
  long long best = -1;

  /*while (!pq.empty()) {
    Rect rect = pq.top();
    pq.pop();
		cout << "Rect: (" << rect.min.x << "," << rect.min.y << ") -> (" << rect.max.x << "," << rect.max.y << ") Area: " << rect.area << endl;
  }
  return;*/
  while (!pq.empty()) {
    Rect rect = pq.top();
    pq.pop();
		bool hasInside = false;
    for (size_t k = 0; k < positions.size(); ++k)
    {
      if(rect.area == 40) {
        cout << "aaa";
			}
      Vec2 p = positions[k];
      if(p.x > rect.min.x && p.x < rect.max.x &&
          p.y >  rect.min.y && p.y < rect.max.y) {
				hasInside = true;
        break;
			}
    }
    if (!hasInside) {
			best = rect.area;
      break;
    }
	}

  cout << "Ex_9 (b): " << best << endl;
}

