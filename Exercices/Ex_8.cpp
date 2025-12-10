#include "Ex_8.h"
#include <unordered_map>
#include <algorithm>
#include <array>
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
			parent[i] = i;   // each element starts in its own set
	}

  int find(int i) {
    if (parent[i] != i)
      parent[i] = find(parent[i]);
    return parent[i];
  }


  bool isRoot(int i) {
    return parent[i] == i;
	}

  int getSize(int i) {
    int root = find(i);
    return size[root];
	}

	bool unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;

		// union by size (attach small group to big group)
		if (size[a] < size[b])
			std::swap(a, b);

		parent[b] = a;
		size[a] += size[b];
    return true;
	}
};

void Ex_8::Run1(ifstream& input)
{
  vector<Vec3> positions;

  string line;
  while (getline(input, line)) {
    int x, y, z;
    if (sscanf_s(line.c_str(), "%d,%d,%d", &x, &y, &z) == 3) {
      positions.push_back({ x, y, z });
    }
  }

  /*for (size_t i = 0; i < positions.size(); i++)
  {
    cout<<positions[i].ToString() << endl;
  }*/

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

  // ---- Process the first N connections ----
  int TARGET_CONNECTIONS = edges.size() > 20 ? 1000 : 1000; // or 10 for sample
  int connections = 0;

  for (const Edge& e : edges) {
    if (connections == TARGET_CONNECTIONS) break;

    // for testing 
    /*cout << "Uniting "
      << positions[e.a_indx].ToString() 
      << " with " 
      << positions[e.b_indx].ToString() 
      << endl;*/
      connections++;
    if( dsu.unite(e.a_indx, e.b_indx)) {
    }
  }

  array<int, 3> sizes{0,0,0};
  for (int i = 0; i < n; i++) {
    bool r = dsu.isRoot(i);
    if (!r) continue;
    int size = dsu.getSize(i);
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

  cout << "Answer = " << result << endl;
}
void Ex_8::Run2(ifstream& input)
{
}
