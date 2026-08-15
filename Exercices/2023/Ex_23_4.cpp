#pragma once
#include "Ex_23_4.h"
#include "../../utils.h"
#include "../../config.h"
#include "../../benchmarker.h"

int getFinds(const string_view str, vector<int>& win_n) {
  size_t end = str.find(':') +2;
  win_n.clear();
    // get winning numbers
    for (size_t i = 0; i < win_n.capacity(); i++, end+=3 ) {
      // g_config cout << utils::svtoi(str.substr(end, 2)) << " ";
      win_n.push_back(utils::svtoi(str.substr(end, 2)));
    }
    // cout << "| ";
    end += 2;
    int finds = 0;
    // check my numbers
    for (size_t i = 0; end < str.size(); i++, end+=3 ) {
      int myNum = utils::svtoi(str.substr(end, 2));
      if(std::find(win_n.begin(), win_n.end(), myNum) == win_n.end()) continue;
      // cout << myNum << " ";
      finds++;
    }
    return finds;
}

void Ex_23_4::Run1(ifstream& input)
{
  cout<<"running Ex_23_4" << '\n';
  string line;
  long long sum = 0;
  vector<int> win_n; // ten is the amount of winning numbers in the input
  win_n.reserve(10);
  while (getline(input, line)) {
    string_view str(line);
    int finds = getFinds(str,win_n);
    int res = 0;
    for (size_t i = 0; i < finds; i++)
    {
      if(res == 0) res = 1;
      else res *= 2;
    }
    
    sum += res;
  }
  utils::println(sum);
}

long dfs(const vector<string>& lines, vector<long>& mem, int id, vector<int>& win_n) {
  if (mem[id] != 0) {
    return mem[id];
  }

  const string& line = lines[id];
  string_view str(line);
  int finds = getFinds(str, win_n);

  long sum = 1;
  for (int i = 1; i <= finds; i++) {
    sum += dfs(lines, mem, id + i, win_n);
  }
  
  mem[id] = sum;
  return sum;
}

void v1(ifstream& input)
{
  string line;
  vector<string> lines;
  vector<int> win_n;
  win_n.reserve(10);
  while (getline(input, line)) {
    lines.push_back(line);
  }

  vector<long> mem(lines.size(), 0);
  long long sum = 0;
  
  for (int i = 0; i < lines.size(); i++) {
    sum += dfs(lines, mem, i, win_n);
  }
  
  // utils::println(sum);
}

void v2(ifstream& input) {
  string line;
  vector<int> matches_per_card;
  vector<int> win_n;
  win_n.reserve(10);

  while (getline(input, line)) {
    string_view str(line);
    int finds = getFinds(str, win_n);    
    matches_per_card.push_back(finds);
  }

  // Start with 1 copy of every card
  vector<long long> card_counts(matches_per_card.size(), 1);

  long long total_cards = 0;

  for (size_t i = 0; i < matches_per_card.size(); i++) {
    int matches = matches_per_card[i];
    
    // If we have matches, add copies to the subsequent cards
    for (int j = 1; j <= matches; j++) {
      if (i + j < card_counts.size()) {
        // We add our current card count to the next cards
        card_counts[i + j] += card_counts[i];
      }
    }
    
    // Accumulate the final count for this card
    total_cards += card_counts[i];
  }

  // cout << total_cards << '\n';
}

void Ex_23_4::Run2(ifstream& input)
{
  cout << "running Ex_23_4 (b)" << '\n';
  v2(input);
  // Benchmarker benchmarker(10000);
  // benchmarker.addFunction("dfs and memoization", [&input]() {
  //   input.clear();  // Reset stream state
  //   input.seekg(0, std::ios::beg);  // Rewind to the beginning
  //   v1(input);
  // });
  // benchmarker.addFunction("AI version", [&input]() {
  //   input.clear();
  //   input.seekg(0, std::ios::beg);
  //   v2(input);
  // });

  // benchmarker.run();
}

// Starting benchmark with 10000 iterations.
// ------------------------------------------------------------
// Function Name                              Average Time (ns)
// ------------------------------------------------------------
// dfs and memoization                              5801830.200                    
// AI version                                       5443467.400                    
// ------------------------------------------------------------