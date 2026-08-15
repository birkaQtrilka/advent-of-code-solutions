#include "Ex_23_4.h"
#include "../../utils.h"
#include "../../config.h"

void Ex_23_4::Run1(ifstream& input)
{
  // bool draw = g_config.find("drawMode") = 1;
  cout<<"running Ex_23_4" << '\n';
  string line;
  long long sum = 0;
  // vector<char> num_char(2);
  vector<int> win_n; // ten is the amount of winning numbers in the input
  win_n.reserve(10);
  while (getline(input, line)) {
    win_n.clear();
    string_view str(line);
    size_t end = line.find(':') +2;

    // get winning numbers
    for (size_t i = 0; i < win_n.capacity(); i++, end+=3 ) {
      // g_config cout << utils::svtoi(str.substr(end, 2)) << " ";
      win_n.push_back(utils::svtoi(str.substr(end, 2)));
    }
    // cout << "| ";
    end += 2;
    int finds = 0;
    // check my numbers
    for (size_t i = 0; end < line.size(); i++, end+=3 ) {
      int myNum = utils::svtoi(str.substr(end, 2));
      if(std::find(win_n.begin(), win_n.end(), myNum) == win_n.end()) continue;
      // cout << myNum << " ";
      if(finds == 0) finds = 1;
      else finds *= 2;
    }
    // cout<<'\n';
    sum += finds;
  }
  utils::println(sum);
}
// int max_depth = 0;
// long test = 0;
long dfs(const vector<string>& lines, vector<long>& mem, int id) {
  if (mem[id] != 0) {
    return mem[id];
  }

  int finds = 0;
  const string& line = lines[id];
  vector<int> win_n;
  string_view str(line);
  
  size_t end = line.find(':') +2;
  // get winning numbers
  for (size_t i = 0; i < 10; i++, end+=3 ) {
    win_n.push_back(utils::svtoi(str.substr(end, 2)));
  }
  end += 2;
  // check my numbers
  for (size_t i = 0; end < line.size(); i++, end+=3 ) {
    int myNum = utils::svtoi(str.substr(end, 2));
    if(std::find(win_n.begin(), win_n.end(), myNum) == win_n.end()) continue;
    finds++;
  }

  long sum = 1;
  for (int i = 1; i <= finds; i++) {
    sum += dfs(lines, mem, id + i);
  }
  
  mem[id] = sum;
  return sum;
}

void Ex_23_4::Run2(ifstream& input)
{
  cout << "running Ex_23_4 (b)" << '\n';
  string line;
  vector<string> lines;
  
  while (getline(input, line)) {
    lines.push_back(line);
  }

  vector<long> mem(lines.size(), 0);
  long long sum = 0;
  
  for (int i = 0; i < lines.size(); i++) {
    sum += dfs(lines, mem, i);
  }
  
  utils::println(sum);
}