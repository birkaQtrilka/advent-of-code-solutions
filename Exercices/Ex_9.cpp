#include "Ex_9.h"
#include <algorithm>
#include "../utils.h"
#include <queue>


void Ex_9::Run1(ifstream& input)
{
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

bool Ex_9::SegmentsIntersect(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4) {
  // Determine which is vertical and which is horizontal
  bool p1p2_vertical = (p1.x == p2.x);
  bool p3p4_vertical = (p3.x == p4.x);

  // If they are parallel (both vert or both horz), they don't "cross" in a 
  // way that creates a hole (overlapping edges are valid boundaries).
  if (p1p2_vertical == p3p4_vertical) return false;

  // Identify the Vertical segment (V) and Horizontal segment (H)
  Vec2 v1 = p1p2_vertical ? p1 : p3; // Vert Start
  Vec2 v2 = p1p2_vertical ? p2 : p4; // Vert End
  Vec2 h1 = p1p2_vertical ? p3 : p1; // Horz Start
  Vec2 h2 = p1p2_vertical ? p4 : p2; // Horz End

  // Check strict crossing:
  // Vertical X must be strictly between Horizontal X range
  // Horizontal Y must be strictly between Vertical Y range
  bool x_overlaps = v1.x > std::min(h1.x, h2.x) && v1.x < std::max(h1.x, h2.x);
  bool y_overlaps = h1.y > std::min(v1.y, v2.y) && h1.y < std::max(v1.y, v2.y);

  return x_overlaps && y_overlaps;
}

bool Ex_9::IsRectInPolygon(Rect r, const std::vector<Vec2>& poly) {
  int n = poly.size();
	Vec2 tR = { r.max.x, r.min.y };
	Vec2 bL = { r.min.x, r.max.y };
  points[0] = PointData(r.min, tR);
  points[1] = PointData(r.max, bL);
  points[2] = PointData(bL, r.min);
  points[3] = PointData(tR, r.max);

  for (int i = 0, j = n - 1; i < n; j = i++) {
    Vec2 a = poly[i];
		Vec2 b = poly[j];
    for (int i = points.size() - 1; i >= 0; i--)
    {
			PointData& pointData = points[i];
      if (SegmentsIntersect(a, b, pointData.p, pointData.other)) {
        return false; // Polygon edge cuts through the rectangle
      }
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
    pq.pop();
		
    if (IsRectInPolygon(rect, positions)) {
			best = rect.area;
      break;
    }
	}

  cout << "Ex_9 (b): " << best << endl;
}