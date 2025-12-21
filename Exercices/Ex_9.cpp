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
class PointData {
  public:
    bool inside = false;
    bool onSegment = false;
		Vec2 p;
		PointData(Vec2 point) : p(point) {}
};
bool Ex_9::IsRectInPolygon(Rect r, const std::vector<Vec2>& poly) {
  int n = poly.size();

  vector<PointData> points{
    PointData(r.min),
    PointData(r.max),
    PointData({r.min.x, r.max.y}),
    PointData({r.max.x, r.min.y}),
  };

  for (int i = 0, j = n - 1; i < n; j = i++) {
    Vec2 a = poly[i];
		Vec2 b = poly[j];
    for (int i = points.size() - 1; i >= 0; i--)
    {
			PointData& pointData = points[i];
      if(pointData.onSegment) continue;

      if(OnSegment(pointData.p, a, b)) {
        pointData.onSegment = true;
        pointData.inside = true;
        continue;
			}

      IsPointInPolygon(pointData.p, a, b, pointData.inside);

    }
    
  }

  return std::all_of(points.begin(), points.end(),
    [](const PointData& p) {
      return p.inside;
    });
}
// 4630762112 too high
bool Ex_9::OnSegment(Vec2 p, Vec2 a, Vec2 b) {
  // Case 1: Vertical Edge (Same Column)
  if (a.x == b.x) {
    if (p.x != a.x) return false; // Not in same column
    return p.y >= std::min(a.y, b.y) && p.y <= std::max(a.y, b.y);
  }

  if (p.y != a.y) return false; // Not in same row
  return p.x >= std::min(a.x, b.x) && p.x <= std::max(a.x, b.x);
}

void Ex_9::IsPointInPolygon(Vec2 p, Vec2 a, Vec2 b, bool& inside) {
  if (
		  a.x == b.x && // vertical edge
      ((a.y > p.y) != (b.y > p.y)) && // between y of a and b
      p.x < a.x // to the left of the edge (a crossing)
    ) {
    inside = !inside;
  }
}

void Ex_9::Run2(ifstream& input)
{
  vector<Vec2> positions;
  string line;

  while (getline(input, line)) {
    int x, y;
    sscanf_s(line.c_str(), "%d,%d", &x, &y);

    positions.push_back({ x, y });
  }
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
  while (!pq.empty()) {
    Rect rect = pq.top();
    /*if(rect.area == 24) {
			cout << "";
		}*/
    pq.pop();
		
    if (IsRectInPolygon(rect, positions)) {
			best = rect.area;
      break;
    }
	}

  cout << "Ex_9 (b): " << best << endl;
}



