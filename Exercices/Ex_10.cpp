#pragma once
#include "Ex_10.h"
#include <regex>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>

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

  ForEachContent(line, "(", ")", [&](string r) {
    Button btn;
    GetNumber(r, [&](int n) {
      btn.affects.push_back(n);
    });
    schematics.push_back(move(btn));
    });

  priority_queue<Node> q;
  unordered_map<VecN, int, VecNHash> dist;
  int dimensions = target.size();
  VecN startPos = { dimensions };
  q.push({ 0, startPos});
  dist[startPos] = 0;

  while (!q.empty()) {
    Node top = q.top();
    q.pop();

    int minToStart = top.distanceToStart;
    VecN& minNode = top.pos;

    auto itr = dist.find(minNode);

    if (itr != dist.end() && minToStart > itr->second) {
      continue;
    }

    if (minNode.Equals(target)) return minToStart;

    // problem here is that nodes represent positions, but I have displacements
    for (size_t i = 0; i < schematics.size(); i++)
    {
      // w is number of presses, which is 1 every time
      VecN connection = minNode;
      bool prune = false;
      for (int idx : schematics[i].affects) {
        connection.data[idx]++;
        if (connection.data[idx] > target[idx]) {
          prune = true;
          break;
        }
      }
      if (prune) continue;
      int distanceToStart = 1 + minToStart;
      // heuristics

      auto it = dist.find(connection);

      if (it == dist.end()) {
        q.push({ distanceToStart, connection });
        dist[connection] = distanceToStart;
        continue;
      }

      bool pathIsNotCloser = it->second < distanceToStart /*+ heuristics*/;
      if (pathIsNotCloser) continue;
      q.push({ distanceToStart, connection });
      it->second = distanceToStart;
    }
  }

  return -1;
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