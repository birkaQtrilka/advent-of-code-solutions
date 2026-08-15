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
long dfs(ifstream& input, string& line, vector<int>& win_n, vector<long>& mem, int id) {
  int finds = 0;
  if(mem.size() <= id) {
    getline(input, line);
    win_n.clear();
    string_view str(line);
    size_t end = line.find(':') + 2;
    // utils::println(str.substr(0,end));

    // get winning numbers
    for (size_t i = 0; i < win_n.capacity(); i++, end+=3 ) {
      win_n.push_back(utils::svtoi(str.substr(end, 2)));
    }
    end += 2;
    // check my numbers
    // int s = 0;
    for (size_t i = 0; end < line.size(); i++, end+=3 ) {
      if(std::find(win_n.begin(), win_n.end(), utils::svtoi(str.substr(end, 2))) == win_n.end()) continue;
      finds += 1;
      // if(s == 0) s = 1;
      // else s*= 2;
    }
    // test += s;
    mem.push_back(0);
  }
  else {
    return mem[id];
  }
  // int currentID = id;

  if(finds == 0) {
    mem[id] = 1;
    // max_depth = std::max(id, max_depth);
    return 1;
  }
  else {
    long sum = 1; 
    for (size_t i = 0; i < finds; i++)
    {
      id++;
      if(mem.size() <= id){
        mem[id] = dfs(input, line, win_n, mem, id);
      }
      sum += mem[id];
    }
    return sum;
  }
}

void Ex_23_4::Run2(ifstream& input)
{
  cout << "running Ex_23_4 (b)" << '\n';
  string line;
  vector<int> win_n;
  win_n.reserve(10);
  vector<long> mem;
  long long sum = 0;
  int i = 0;
  while(input.peek() != EOF){
    sum += dfs(input, line, win_n, mem, i++);
    // utils::println(sum);

  }
  utils::println(sum);
  // utils::println(test);
}
