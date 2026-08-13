#include "Ex_25_8.h"
#include <unordered_map>
#include <algorithm>
#include <array>
#include <queue>

struct Vec3 {
	int x = 0;
	int y = 0;
	int z = 0;


  long long DistanceTo(const Vec3& other) const {
    // Store differences as long long to prevent overflow during multiplication
    long long dx = x - other.x;
    long long dy = y - other.y;
    long long dz = z - other.z;
    return (dx * dx + dy * dy + dz * dz);
  }

  string ToString() {
    return (to_string(x) + "," + to_string(y) + "," + to_string(z));
  }
};

struct Edge {
  int a_indx;
  int b_indx;
  long long dist;

  bool operator<(const Edge& other) const {
    return dist < other.dist;
  }
};

struct DSU {
private:
  vector<int> parent;
	vector<int> size;
public:
	DSU(int n) {
		parent.resize(n);
		size.resize(n, 1);
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

  int Find(int i) {
    if (parent[i] != i)
      parent[i] = Find(parent[i]);
    return parent[i];
  }

  bool IsRoot(int i) {
    return parent[i] == i;
	}

  int GroupSize(int i) {
    int root = Find(i);
    return size[root];
	}

	bool Unite(int a, int b) {
		a = Find(a);
		b = Find(b);
		if (a == b) return false;

		if (size[a] < size[b])
			std::swap(a, b);

		parent[b] = a;
		size[a] += size[b];
    return true;
	}
};

void Ex_25_8::Run2(ifstream& input)
{
  vector<Vec3> positions;

  string line;
  while (getline(input, line)) {
    int x, y, z;
    if (sscanf_s(line.c_str(), "%d,%d,%d", &x, &y, &z) == 3) {
      positions.push_back({ x, y, z });
    }
  }

  int n = positions.size();
  DSU dsu(n);

  vector<Edge> edges;
  edges.reserve(n * (n - 1) / 2);

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      long long d2 = positions[i].DistanceTo(positions[j]);
      edges.push_back({ i, j, d2 });
    }
  }

  sort(edges.begin(), edges.end(),
    [](const Edge& a, const Edge& b) { return a.dist < b.dist; });
  int last_a = 0;
  int last_b = 0;
  for (const Edge& e : edges) {

    dsu.Unite(e.a_indx, e.b_indx);
    if (dsu.GroupSize(dsu.Find(e.a_indx)) == n) {
      last_a = e.a_indx;
      last_b = e.b_indx;
      break;
    }
  }


  long long result = 1LL * positions[last_a].x * positions[last_b].x;
  cout << "Ex_25_8 (b): " << result << endl;
}

void Ex_25_8::Run1(ifstream& input)
{
  vector<Vec3> positions;

  string line;
  while (getline(input, line)) {
    int x, y, z;
    if (sscanf_s(line.c_str(), "%d,%d,%d", &x, &y, &z) == 3) {
      positions.push_back({ x, y, z });
    }
  }
  int TARGET_CONNECTIONS = 1000; // 1000 for solution or 10 for sample
  int n = positions.size();
  priority_queue<Edge> pq;

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      long long d2 = positions[i].DistanceTo(positions[j]);

      if (pq.size() < TARGET_CONNECTIONS) {
        pq.push({ i, j, d2 });
      }
      else if (d2 < pq.top().dist) {
        // If this edge is smaller than the worst edge in our top list,
        // swap them out.
        pq.pop();
        pq.push({ i, j, d2 });
      }
    }
  }

  vector<Edge> best_edges;
  best_edges.reserve(TARGET_CONNECTIONS);
  while (!pq.empty()) {
    best_edges.push_back(pq.top());
    pq.pop();
  }

  DSU dsu(n);
  int connections = 0;
  for (const Edge& e : best_edges) {
    //if (connections == TARGET_CONNECTIONS) break;
    connections++;
    dsu.Unite(e.a_indx, e.b_indx);
  }

  array<int, 3> sizes{ 0,0,0 };
  // getting 3 highest sets
  for (int i = 0; i < n; i++) {
    bool r = dsu.IsRoot(i);
    if (!r) continue;
    int size = dsu.GroupSize(i);
    for (size_t j = 0; j < 3; j++) {
      if (size <= sizes[j]) continue;
      // shifting
      int prevTemp = size;
      for (size_t k = j; k < 3; k++)
      {
        int temp = sizes[k];
        sizes[k] = prevTemp;
        prevTemp = temp;
      }
      break;
    }
  }


  long long result = 1LL * sizes[0] * sizes[1] * sizes[2];

  cout << "Ex_25_8: " << result << endl;
}
