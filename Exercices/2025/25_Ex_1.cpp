
/*Part One – Count times the dial ends on 0

You are given a list of rotations on a circular dial numbered 0–99, starting at 50.
Each rotation moves the dial left (decreasing numbers) or right (increasing numbers), wrapping around at both ends.

--> How many times does the dial land exactly on 0 after completing a rotation?

Part Two – Count every time the dial clicks past 0

Now you must count every individual click where the dial passes or lands on 0, including:
When a rotation finishes at 0
When the dial rolls past 0 during a long rotation (e.g., L68, R1000)

--> How many total clicks (endpoints + intermediate steps) cause the dial to point at 0?
*/

#include "25_Ex_1.h"

struct LockEntry {
	int dir = 0;
	int distance = 0;
};

void Ex_1::Run1(ifstream& input)
{
	int CAP = 100;
	string line;
	vector<LockEntry> entries;
	while (getline(input, line)) {
		LockEntry entry;
		entry.dir = line[0] == 'L' ? -1 : 1;
		entry.distance = stoi(line.substr(1)) % CAP; // capping already to correctly wrap
		entries.push_back(entry);
	}
	int currentIndex = 50;
	int count = 0;
	for (auto& entry : entries) {
		currentIndex += entry.dir * entry.distance;
		if (currentIndex < 0) currentIndex = CAP + currentIndex;
		else if (currentIndex >= CAP) currentIndex = currentIndex - CAP;
		count += currentIndex == 0;
	}
	cout << "Number of times at 0: " << count << endl;
}

void Ex_1::Run2(ifstream& input)
{
	// parsing -------
	int CAP = 100;
	string line;
	vector<LockEntry> entries;
	while (getline(input, line)) {
		LockEntry entry;
		entry.dir = line[0] == 'L' ? -1 : 1;
		entry.distance = stoi(line.substr(1));
		entries.push_back(entry);
	}
	// parsing -------

	int currentIndex = 50;
	int count = 0;
	for (auto& entry : entries) {
		int crosses = 0;
		if (entry.dir == 1) {
			crosses = (currentIndex + entry.distance) / CAP;
		}
		else {
			int flip = CAP - currentIndex;
			crosses = (flip + entry.distance) / CAP;
			if (currentIndex == 0) crosses--; // if already landed at 0, it will always count as cross, so remove it
		}

		currentIndex = (currentIndex + entry.dir * entry.distance) % CAP;
		currentIndex += CAP * (currentIndex < 0);

		count += crosses;
	}
	cout << "Ex_1 (b): " << count << endl;

}