#include "Ex_10.h"
#include <regex>
#include <sstream>

void Ex_10::Toggle(uint32_t& bits, int i) {
  bits ^= (1u << i);
}

string Ex_10::ToBitString(uint32_t value) {
  string result;
  result.reserve(32);

  for (int i = 31; i >= 0; --i) {
    result.push_back(((value >> i) & 1u) ? '1' : '0');
  }

  return result;
}

void Ex_10::Run1(ifstream& input)
{
	string line;
	while(getline(input, line))
	{
		AnalyzeLine(line);
		cout << endl << "===================" << endl << endl;
  }

}

void Ex_10::AnalyzeLine(const string& line)
{
  uint32_t target = 0;
  vector<uint32_t> round;
  cout << "Target: " << endl;
  ForEachContent(line, "[", "]", [&](string r) {
    for (size_t i = 0; i < r.size(); i++) {
      if (r[i] == '#') Toggle(target, i);
    }
    cout << ToBitString(target) << endl;
    });
  cout << "Buttons: " << endl;

  ForEachContent(line, "(", ")", [&](string r) {
    round.push_back(0);
    GetNumber(r, [&](int n) {
      Toggle(round.back(), n);
      });
    cout << ToBitString(round.back()) << endl;
    });
  // brute force all combinations
  uint32_t current = 0;
  cout << "Combining: " << endl << endl;

  for (size_t i = 0; i < round.size() - 1; i++) {
    current ^= round[i];
    cout << i << " :    " << ToBitString(current) << endl;
    for (size_t j = i + 1; j < round.size(); j++) {
      current ^= round[j];
      cout << "+ " << j << " =  " << ToBitString(current) << endl;

      if (current == target) {
				cout << "FOUND with buttons: " << i << " and " << j << endl;
        return;
      }
      // clear for next
      current ^= round[j];
    }
    cout << "----" << endl;
    current ^= round[i];

  }
}

void Ex_10::Run2(ifstream& input)
{
}

void Ex_10::ForEachContent(
  const string& line,
  const string& s,
  const string& e,
  const function<void(const string&)>& callback
)
{
  // Escape end delimiter for character class
  string escapedEnd = "\\" + e;

  string pattern =
    "\\" + s +
    "([^" + escapedEnd + "]+)" +
    "\\" + e;

  regex rx(pattern);

  for (auto it = sregex_iterator(line.begin(), line.end(), rx);
    it != sregex_iterator(); ++it)
  {
    callback((*it)[1].str());
  }
}


void Ex_10::GetNumber(string& content, const function<void(int)>& callback)
{
  string token;
  stringstream ss(content);

  while (getline(ss, token, ',')) {
		callback(stoi(token));
  }
}