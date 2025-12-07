
/*Part One – Count fresh available ingredient IDs

The input contains:
- A list of inclusive fresh ID ranges (which may overlap),
- A blank line,
- A list of available ingredient IDs.

An ingredient is fresh if it falls within any fresh ID range.

--> How many of the available ingredient IDs are fresh?

Part Two – Count all IDs covered by fresh ranges

Ignore the list of available IDs.
Combine all fresh ID ranges (including overlaps) and count how many distinct
ingredient IDs they cover.

--> How many total ingredient IDs are considered fresh according to the ranges?
*/


#include "Ex_5.h"
struct Range {
	long long min = 0;
	long long max = 0;
};
void Ex_5::Run1(ifstream& input)
{
	// parsing -------
	string line;
	vector<Range> ranges;
	vector<long long> ids;
	while (getline(input, line)) {
		if (line.empty()) break;
		size_t dashPos = line.find('-');
		string a = line.substr(0, dashPos);
		string b = line.substr(dashPos + 1);
		long long start = stoll(a); 
		long long end = stoll(b);

		ranges.push_back({ start, end });
	}
	while (getline(input, line)) {
		ids.push_back(stoll(line));
		//cout << line << endl;
	}
	// parsing -------

	int count = 0;
	for (size_t i = 0; i < ids.size(); i++)
	{
		long long id = ids[i];
		for (size_t j = 0; j < ranges.size(); j++)
		{
			Range range = ranges[j];
			if (id >= range.min && id <= range.max) {
				count++;
				//cout << id << endl;
				break;
			}
		}
	}

	cout << "Ex_5: " << count << endl;
}

void Ex_5::Run2(ifstream& input)
{
	string line;
	vector<Range> ranges;
	vector<long long> ids;
	while (getline(input, line)) {
		if (line.empty()) break;
		size_t dashPos = line.find('-');
		string a = line.substr(0, dashPos);
		string b = line.substr(dashPos + 1);
		long long start = stoll(a);
		long long end = stoll(b);

		ranges.push_back({ start, end });
	}
	long long count = 0;
	for (size_t j = 0; j < ranges.size() - 1; j++)
	{
		Range& range1 = ranges[j];
		if (range1.min == -1) continue;
		for (size_t i = j + 1; i < ranges.size(); i++)
		{
			Range& range2 = ranges[i];
			if (range2.min == -1) continue;
			// overlaps 
			if (range1.min <= range2.max && range2.min <= range1.max) {
				// combines ranges
				range1.min = min(range1.min, range2.min);
				range1.max = max(range1.max, range2.max);
				j = -1;
				// invalidate range2 to not check it later
				range2.min = -1;
				range2.max = -1;
			}
		}
	}

	for (auto& range : ranges)
	{
		if (range.min == -1) continue;
		count += range.max - range.min + 1;
	}
	cout << "Ex_5 (b): " << count << endl;
}
