
/*Part One – Maximize joltage using two batteries per bank

Each line of digits represents a bank of batteries (each digit = battery joltage 1–9).
You must turn on exactly two batteries per bank. The bank's joltage is the two-digit
number formed by those two chosen digits, in their original order.

--> For each bank, what is the maximum two-digit joltage you can form, and what is the total sum across all banks?

Part Two – Maximize joltage using twelve batteries per bank

Now you must turn on exactly twelve batteries per bank.
The bank's joltage is the 12-digit number formed by the selected digits, in order.

--> For each bank, what is the maximum 12-digit joltage you can form, and what is the total sum across all banks?
*/


#include "Ex_3.h"

void Ex_3::Run1(ifstream& input)
{
	string bank;
	int count = 0;
	while (getline(input, bank)) {
		int bat1 = 0;
		int bat2 = 0;
		int bat2Index = -1;
		// finding biggest 2 digit number
		for (size_t i = 0; i < bank.size() - 1; i++)
		{
			// parsing to int
			int sample1 = bank[i] - '0'; 
			int sample2 = bank[i + 1] - '0';
			if (sample1 > bat1) {
				bat1 = sample1;
				if (i == bat2Index) {
					bat2 = 0;
					bat2Index = 0;
				}
			}
			if (sample2 > bat2) {
				bat2 = sample2;
				bat2Index = i + 1;
			}
		}
		int sum = bat1 * 10 + bat2;
		//cout << "bank highest joltage: " << sum << endl;
		count += sum;
	}
	cout << "Ex_3: " << count << endl;
}

void Ex_3::Run2(ifstream& input)
{
	string bank;
	long long count = 0;
	int BAT_CLUMP = 12;
	while (getline(input, bank)) {
		vector<int> batteries;
		batteries.assign(BAT_CLUMP, 0);
		// it first finds the first biggest number, then 
		int lastBat = 0; // used t
		for (size_t i = 0; i < BAT_CLUMP; i++) {
			// cannot go further than the length of batteries clump
			for (size_t j = lastBat; j < bank.size() - (BAT_CLUMP - i) + 1; j++)
			{
				// look for biggest in range
				int sample = bank[j] - '0'; // parsing to int
				if (sample > batteries[i]) {
					batteries[i] = sample;
					lastBat = j + 1;
				}
			}
		}

		// getting total joltage
		long long sum = 0;
		for (size_t i = 0; i < BAT_CLUMP; i++) {
			sum = sum * 10 + batteries[i];
		}
		//cout << "bank highest joltage: " << sum << endl;
		count += sum;
	}
	cout << "Ex_3 (b): " << count << endl;
}
