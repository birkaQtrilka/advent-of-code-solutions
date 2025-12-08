#include "Ex_8.h"

struct Vec3 {
	int x = 0;
	int y = 0;
	int z = 0;

	int ID = -1;

	float DistanceTo(const Vec3& other) const {
		int dx = x - other.x;
		int dy = y - other.y;
		int dz = z - other.z;
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}
};

void Ex_8::Run1(ifstream& input)
{
	vector<Vec3> positions;
	vector<vector<Vec3>> lookup;
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

	// instead of checking relative closest distances, we need to find the minimum distance globally
	for (size_t i = 0; i < positions.size() - 1; i++) {
		float min = INT_MAX;
		int min_index = -1;
		Vec3& vec_a = positions[i];

		for (size_t j = i + 1; j < positions.size(); j++) {
			if (positions[j].ID == -1 && vec_a.DistanceTo(positions[j]) < min) {
				min = vec_a.DistanceTo(positions[j]); // need to avoid if they are already linked
				min_index = j;
			}
		}
		if (min_index == -1) break; // all others are linked already
		Vec3& vec_b = positions[min_index];
		if (vec_b.ID == -1) {
			vec_a.ID = ID;
			vec_b.ID = ID;
			lookup.push_back({});
			vector<Vec3>& newGroup = lookup[ID];
			newGroup.push_back(vec_a);
			newGroup.push_back(vec_b);
			ID++;
		}
		else {
			// if position[i] doesn't have an ID, assign it the min_index ID
			// if it does and is different,merge the two groups
			// if it does and is same ID as min_index, do nothing
			
			if (vec_a.ID == -1) {
				vec_a.ID = vec_b.ID;
				lookup[vec_b.ID].push_back(vec_a);
			}
			else if (vec_a.ID != vec_b.ID) {
				auto& arr1 = lookup[vec_a.ID];
				auto& arr2 = lookup[vec_b.ID];
				// reassigning IDs
				for (auto& v : arr2) {
					v.ID = vec_a.ID;
				}
				// merging
				arr1.insert(arr1.end(), arr2.begin(), arr2.end());
				arr2.clear();
			}
			
		}
	}

	cout << "Ex_8: " << lookup.size() << endl;
}

void Ex_8::Run2(ifstream& input)
{
}
