/*Part One – Solve vertical math problems left-to-right

The worksheet contains several problems arranged side-by-side horizontally.
Each problem consists of numbers stacked vertically with an operator (+ or *)
at the bottom. A full column of spaces separates problems.

For each problem, read its numbers top-to-bottom in the same column group
(left-to-right across the worksheet), apply the operator, and sum all results.
you also need to unroll the input, so the operators sit in one line, and the above columns match it

--> What is the grand total of all problem results?

Part Two – Solve vertical math problems right-to-left (cephalopod math)

Numbers are still stacked vertically, but now each column represents one number
(most significant digit at the top). Problems are read right-to-left, one column
group at a time. Apply the operator at the bottom of each column group.

--> What is the grand total when problems are evaluated using right-to-left column reading?
*/


#include "Ex_6.h"
#include <chrono>

void Ex_6::Run1(ifstream& input) {
  if (true) {
    Run11(input);
    return;
  }
  stringstream buffer;
  buffer << input.rdbuf();
  string fileContents = buffer.str();

  cout << "=== Algorithm Benchmark ===" << endl;
  cout << "Running each algorithm 100 times..." << endl << endl;

  const int iterations = 1000;

  // Benchmark Run11 (original)
  auto start11 = chrono::high_resolution_clock::now();
  long long result11;
  for (int i = 0; i < iterations; i++) {
    stringstream ss(fileContents);
    ifstream mockInput;
    // Create a temporary stringstream to act as input
    stringstream tempStream(fileContents);
    Run11(tempStream);
  }
  auto end11 = chrono::high_resolution_clock::now();
  auto duration11 = chrono::duration_cast<chrono::microseconds>(end11 - start11);

  // Benchmark Run12 (optimized)
  auto start12 = chrono::high_resolution_clock::now();
  long long result12;
  for (int i = 0; i < iterations; i++) {
    stringstream tempStream(fileContents);
    Run12(tempStream);
  }
  auto end12 = chrono::high_resolution_clock::now();
  auto duration12 = chrono::duration_cast<chrono::microseconds>(end12 - start12);

  // Print results
  cout << "\n=== Benchmark Results ===" << endl;
  cout << "Run11 (Original):  " << duration11.count() / 1000.0 << " ms total, "
    << duration11.count() / (double)iterations / 1000.0 << " ms average" << endl;
  cout << "Run12 (Optimized): " << duration12.count() / 1000.0 << " ms total, "
    << duration12.count() / (double)iterations / 1000.0 << " ms average" << endl;

  double speedup = (double)duration11.count() / duration12.count();
  cout << "\nSpeedup: " << speedup << "x faster" << endl;
  cout << "Time saved: " << (duration11.count() - duration12.count()) / 1000.0 << " ms total, "
    << (duration11.count() - duration12.count()) / (double)iterations / 1000.0 << " ms per run" << endl;
}

// Original algorithm
void Ex_6::Run11(istream& input) {
  // parsing -------
  string line;
  vector<vector<int>> unrolledProblems;
  vector<string> operators;

  while (getline(input, line)) {
    if (line[0] == '+' || line[0] == '*') break;
    stringstream ss(line);
    string t;
    vector<int> nums;
    while (ss >> t) {
      nums.push_back(stoi(t));
    }
    unrolledProblems.push_back(nums);
  }

  do {
    stringstream ss(line);
    string t;
    while (ss >> t) {
      operators.push_back(t);
    }
  } while (getline(input, line));
  // parsing -------

  int width = operators.size();
  // aligns columns to have the same count as operators count
  vector<vector<int>> result = AlignVectors(unrolledProblems, width);
  long long count = 0;

  for (size_t i = 0; i < operators.size(); i++) {
    long long math;
    if (operators[i] == "+") {
      math = 0;
      for (vector<int>& list : result) {
        math += list[i];
      }
    }
    else {
      math = 1;
      for (vector<int>& list : result) {
        math *= list[i];
      }
    }
    count += math;
  }

  cout << "Ex_6: " << count << endl;
}
vector<vector<int>> Ex_6::AlignVectors(const vector<vector<int>>& input, int chunkSize) {
  vector<vector<int>> result;
  vector<int> current;
  current.reserve(chunkSize * 2);

  for (const auto& vec : input) {
    for (int num : vec) {
      current.push_back(num);

      if (current.size() == chunkSize) {
        result.push_back(current);
        current.clear();
      }
    }
  }

  if (!current.empty()) {
    result.push_back(current);
  }

  return result;
}
void Ex_6::Run12(istream& input) {
  string line;

  // --- First pass: read all number vectors ---
  vector<vector<int>> numbers;
  numbers.reserve(256); // heuristic reserve

  while (getline(input, line)) {
    if (line.empty()) continue;
    if (line[0] == '+' || line[0] == '*') break;

    vector<int> row;
    row.reserve(64); // heuristic
    const char* p = line.c_str();

    // Faster integer parsing than stringstream
    while (*p) {
      while (*p == ' ') p++;
      if (!*p) break;

      int sign = 1;
      if (*p == '-') { sign = -1; p++; }

      int val = 0;
      while (*p >= '0' && *p <= '9') {
        val = val * 10 + (*p - '0');
        p++;
      }
      row.push_back(val * sign);
    }
    numbers.push_back(std::move(row));
  }

  // --- Second pass: read operators ---
  vector<bool> isAdd;
  isAdd.reserve(256);

  do {
    if (line.empty()) continue;
    const char* p = line.c_str();
    while (*p) {
      if (*p == '+') isAdd.push_back(true);
      else if (*p == '*') isAdd.push_back(false);
      p++;
    }
  } while (getline(input, line));

  int width = static_cast<int>(isAdd.size());
  long long total = 0;

  // --- Perform computation in rolling chunks (no AlignVectors needed) ---
  vector<long long> accum(width);
  bool firstChunk = true;

  size_t globalIndex = 0;

  for (const auto& row : numbers) {
    for (int n : row) {
      int i = globalIndex % width;

      if (globalIndex < (size_t)width) {
        // initialization of first chunk
        accum[i] = isAdd[i] ? 0LL : 1LL;
      }

      if (isAdd[i]) accum[i] += n;
      else          accum[i] *= n;

      globalIndex++;
    }
  }

  // Sum all results
  for (long long v : accum) total += v;

  // No output (benchmarking mode)
  // cout << "Ex_6 (Run12): " << total << endl;
}

void Ex_6::Run2(ifstream& input)
{
	string line;
	string unrolledProblems;
	while (getline(input, line)) {
		if (line[0] == '+' || line[0] == '*') break;
		unrolledProblems += line;
	}
	vector<string> operators;
	int chunkSize = 0;
  // getting operators including white spaces
	do {
		int start = 0;
		int l = 0;
		for (size_t i = 1; i < line.size(); i++)
		{
			if (line[i] == '+' || line[i] == '*') {
				operators.push_back(line.substr(start, l + 1));
				chunkSize += l+1;
				l = 0;
				start = i ;
				continue;
			}
			l++;
		}
		operators.push_back(line.substr(start));
		chunkSize += l+1;
	} while (getline(input, line));

	vector<string> rolledProblems;
	for (size_t i = 0; i < unrolledProblems.size(); i += chunkSize) {
		rolledProblems.push_back(unrolledProblems.substr(i, chunkSize));
	}
	
	long long count = 0;
	int start = 0;
	for (size_t i = 0; i < operators.size(); i++)
	{
		vector<string> math;
		math.assign(operators[i].size(), "");
		for (string& row : rolledProblems)
		{
			string cell = row.substr(start, operators[i].size());
			for (size_t j = 0; j < cell.size(); j++)
			{
				if (cell[j] == ' ') continue;
				math[j].push_back(cell[j]);
			}
		}
		long long totalSum = 0;
		
		if (operators[i][0] == '+') {
			for (string& m : math) {
				if (m == "") continue;
				totalSum += stoll(m);
			}
		}
		else {
			totalSum = 1;
			for (string& m : math) {
				if (m == "") continue;
				totalSum *= stoll(m);
			}
		}
		
		count += totalSum;
		start += operators[i].size();
	}

	cout << "Ex_6 (b): " << count << endl;
}
