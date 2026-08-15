#include "Ex_23_5.h"
#include "../../utils.h"
#include <array>
#include <limits>

struct Mapping {
  size_t a;
  size_t b;
  size_t range;
};

size_t popNext(size_t& offset, string_view str) {
  size_t count = str.substr(offset, str.size() - offset).find(' ');
  bool endline = count == -1;
  if(endline) {
    count = str.size() - offset;
  }

  auto sv = str.substr(offset, count);
  size_t num = utils::svtol(str.substr(offset, count));
  offset+=count+1;
  return num;
}

void Ex_23_5::Run1(ifstream& input)
{
  cout<<"running Ex_23_5"<< '\n';
  string line;
  size_t sum = 0;
  vector<int> seeds;
  // getting seeds
  getline(input, line);
  string_view str(line);
  size_t end = str.find(':') + 2;
  for (size_t i = 0; end < str.size(); i++)
  {
    size_t num = popNext(end, str);
    seeds.push_back(num);
  }
  getline(input, line);
  getline(input, line);
  int map_i = 0;
  array<vector<Mapping>, 7> mappings;

  while (getline(input, line)) {
    if(line.empty()){
      getline(input, line);
      map_i++;
      continue;
    }
    size_t offset = 0;
    string_view str(line);
    size_t a = popNext(offset, str);
    size_t b = popNext(offset, str);
    size_t range = popNext(offset, str);
    // cout << " " << a << " " << b << " " << range << '\n';
    mappings[map_i].push_back(Mapping {a, b, range});
  }
  size_t result = std::numeric_limits<size_t>::max();
  for (auto &&seed : seeds)
  {
    size_t mapped_val = seed;
    for (auto &&map : mappings)
    {
      for (auto &&range : map)
      {
        if(mapped_val >= range.b && mapped_val < range.b + range.range) {
          size_t normed = mapped_val - range.b;
          mapped_val = range.a + normed;
          break;
        }
      }
      
    }
    result = min(result, mapped_val);
  }
  utils::println(result);
}

void Ex_23_5::Run2(ifstream& input)
{
  cout<<"running Ex_23_5 (b)" << '\n';
  string line;
  size_t sum = 0;
  while (getline(input, line)) {

  }
}
