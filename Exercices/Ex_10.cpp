#include "Ex_10.h"
#include <regex>
#include <sstream>
#include <queue>

void Ex_10::Run1(ifstream& input)
{
  return;
	string line;
	int total = 0;
	while(getline(input, line))
	{
		total += AnalyzeLine(line);
  }
	cout << "Ex_10: " << total << endl;
}

void Ex_10::Run2(ifstream& input)
{
  string line;
  int total = 0;
  while (getline(input, line))
  {
    total += AnalyzeLine2(line);
  }
  cout << "Ex_10 (b): " << total << endl;
}

int Ex_10::AnalyzeLine(const string& line)
{
  uint32_t target = 0;
  vector<uint32_t> schematics;
  ForEachContent(line, "[", "]", [&](string r) {
    for (size_t i = 0; i < r.size(); i++) {
      if (r[i] == '#') Toggle(target, i);
    }
  });

  ForEachContent(line, "(", ")", [&](string r) {
    schematics.push_back(0);
    GetNumber(r, [&](int n) {
      Toggle(schematics.back(), n);
    });
  });
  queue<Combination> q;
  q.push({ 0, 0, 0 });

  while (!q.empty()) {
    Combination node = q.front();
    q.pop();

    for (int i = node.start; i < (int)schematics.size(); i++) {
      uint32_t r = node.result ^ schematics[i];

      if (r == target) {
        return node.depth + 1;
      }

      q.push({ i + 1, node.depth + 1, r });
    }
  }

	return 0;
}

int Ex_10::AnalyzeLine2(const string& line)
{
  vector<Button> schematics;
  vector<int> target;
  
  ForEachContent(line, "{", "}", [&](string r) {
    GetNumber(r, [&](int n) {
      target.push_back(n);
      });
    });
  // setting touched state of each battery
  // 0..000011..n
  uint32_t activeBats = (1 << target.size()) - 1;

  ForEachContent(line, "(", ")", [&](string r) {
    Button btn;
    GetNumber(r, [&](int n) {
      btn.affects.push_back(n);
      //Toggle(btn.mask, n);
    });
    // Determine max presses for this button
    int min = INT_MAX;
    for (auto& i : btn.affects) {
      min = std::min(min, target[i]);
    }
    btn.maxPresses = min;
    schematics.push_back(move(btn));
    });
  queue<Combination2> q;
  vector<int> r;
  r.assign(target.size(), 0);
  q.push({0,0,move(r)});

  int minPresses = INT_MAX;

  while (!q.empty()) {
    Combination2 node = q.front();
    q.pop();
    if (node.presses > minPresses) continue;

    for (int i = node.start; i < (int)schematics.size(); i++) {
      //uint32_t r = node.affectedButtons & ~schematics[i].mask;// 0100 + 0100 -> 0000, 0100 + 0010 -> 0100

      //if (r != 0) {// checking if combination touches all batteries
      //  if (node.presses + 1 > minPresses) continue;
      //  continue;
      //}

      for (int j = 1; j <= schematics[i].maxPresses; j++)
      {
        if (node.presses + j > minPresses) continue;

        vector<int> r = node.result;
        for (size_t k = 0; k < schematics[i].affects.size(); k++){
          int index = schematics[i].affects[k];
          r[index] = node.result[index] + j;
        }
        bool same = true;
        bool invalid = false;
        for (size_t k = 0; k < target.size(); k++) {
          if (r[k] > target[k]) {
            invalid = true;
            break;
          }if (r[k] == target[k]) continue;
          same = false;
        }
        if (same) minPresses = node.presses + j;
        else q.push({ i + 1, (node.presses + j), move(r) });

      }
    }
  }

  return minPresses;
}

void Ex_10::ForEachContent(
  const string& line,
  const string& s,
  const string& e,
  const function<void(const string&)>& callback
)
{
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