#include "Ex_8.h"
#include <unordered_map>
#include <algorithm>
struct Vec3 {
	int x = 0;
	int y = 0;
	int z = 0;


	float DistanceTo(const Vec3& other) const {
		int dx = x - other.x;
		int dy = y - other.y;
		int dz = z - other.z;
		return float(dx * dx + dy * dy + dz * dz);
	}

  string ToString() {
    return (to_string(x) + "," + to_string(y) + "," + to_string(z));
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
			parent[i] = i;   // each element starts in its own set
	}

	int find(int i) {
    if (parent[i] == i) {
      return i;
    }

    return find(parent[i]);
	}

  bool isRoot(int i) {
    return parent[i] == i;
	}

  int getSize(int i) {
    int root = find(i);
    return size[root];
	}

	void unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return;

		// union by size (attach small group to big group)
		if (size[a] < size[b])
			std::swap(a, b);

		parent[b] = a;
		size[a] += size[b];
	}
};

struct Edge {
	int a_indx;
	int b_indx;
	float dist;
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
      float d2 = positions[i].DistanceTo(positions[j]);
      edges.push_back({ i, j, d2 });
    }
  }

  sort(edges.begin(), edges.end(),
    [](const Edge& a, const Edge& b) { return a.dist < b.dist; });

  // ---- Process the first N connections ----
  int TARGET_CONNECTIONS = 10; // or 10 for sample
  int connections = 0;

  for (const Edge& e : edges) {
    if (connections == TARGET_CONNECTIONS) break;

    connections++;
    // for testing 
    /*cout << "Uniting "
      << positions[e.a_indx].ToString() 
      << " with " 
      << positions[e.b_indx].ToString() 
      << endl;*/
    dsu.unite(e.a_indx, e.b_indx);
  }

  vector<int> sizes;
  sizes.reserve(1000);

  for (int i = 0; i < n; i++) {
    bool r = dsu.isRoot(i);
		if (r) sizes.push_back(dsu.getSize(i));
  }

  sort(sizes.begin(), sizes.end(), greater<int>());

  long long result = 1LL * sizes[0] * sizes[1] * sizes[2];

  cout << "Answer = " << result << endl;
}
void Ex_8::Run2(ifstream& input)
{
}
