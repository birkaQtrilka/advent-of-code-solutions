#include "Ex_8.h"

struct Vec3 {
	int ID = -1;
	int x = 0;
	int y = 0;
	int z = 0;


	float DistanceTo(const Vec3& other) const {
		int dx = x - other.x;
		int dy = y - other.y;
		int dz = z - other.z;
		return float(dx * dx + dy * dy + dz * dz);
	}
};

void Ex_8::Run1(ifstream& input)
{
	vector<Vec3> positions;
	vector<vector<int>> lookup;
	int ID = 0;

	string line;
	while (getline(input, line)) {
			Vec3 pos;
			sscanf_s(line.c_str(), "%d,%d,%d", &pos.x, &pos.y, &pos.z);
			positions.push_back(pos);
	}
	// on finding nearest position, check if the item has a valid id, 
	// if not, create it and add both on lookup table
	// id is also the position in lookup table
	// if yes, just add the other one to the existing id
	// put all positions in a lookup table
	int merges = 0;
	const int TARGET_MERGES = 10;
	// instead of checking relative closest distances, we need to find the minimum distance globally
	while (merges < TARGET_MERGES) {
		float min = INT_MAX;
		int min_index_a = -1;
		int min_index_b = -1;
		// space partitioning could be used to optimize this search
		for (size_t i = 0; i < positions.size() - 1; i++) {
			Vec3& v1 = positions[i];
			for (size_t j = i + 1; j < positions.size(); j++) {
				Vec3& v2 = positions[j];
				if ((v1.ID == -1 || v2.ID == -1 || v2.ID != v1.ID) && v1.DistanceTo(v2) < min) {
					min = v1.DistanceTo(v2); // need to avoid if they are already linked
					min_index_a = i;
					min_index_b = j;
				}
			}
		}
		if (min_index_a == -1) break; // all others are linked already
		Vec3& vec_a = positions[min_index_a];
		Vec3& vec_b = positions[min_index_b];


		if (vec_b.ID == -1) {
			// need to check if vec_a has id or not
			if(vec_a.ID == -1) {
				// create new ID
				vec_a.ID = ID;
				vec_b.ID = ID;
				lookup.push_back(vector<int>{ min_index_a, min_index_b });
				merges++;
				ID++;
			}
			else {
				// assign vec_b the vec_a ID
				vec_b.ID = vec_a.ID;
				lookup[vec_a.ID].push_back(min_index_b);
				merges++;
			}

		}
		else {
			// if position[i] doesn't have an ID, assign it the min_index ID
			// if it does and is different,merge the two groups
			// if it does and is same ID as min_index, do nothing

			if (vec_a.ID == -1) {
				vec_a.ID = vec_b.ID;
				lookup[vec_b.ID].push_back(min_index_a);
				merges++;
			}
			else if (vec_a.ID != vec_b.ID) {
				auto& arr1 = lookup[vec_a.ID];
				auto& arr2 = lookup[vec_b.ID];
				// reassigning IDs
				for (int idx : arr2) {
					positions[idx].ID = vec_a.ID;
				}
				// merging
				arr1.insert(arr1.end(), arr2.begin(), arr2.end());
				arr2.clear();
				merges++;
			}
		}
	}


	cout << "Ex_8: " << lookup.size() << endl;
}
//https://chatgpt.com/c/693683ba-2760-8329-a046-c0ba30d77904
void Ex_8::Run2(ifstream& input)
{
}
