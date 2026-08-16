#include "Ex_23_5.h"
#include "../../utils.h"
#include <array>
#include <limits>
#include <queue>

struct Mapping {
  size_t a;
  size_t b;
  size_t range;
};

size_t popNext(size_t& offset, string_view str) {
  size_t space_pos = str.find(' ', offset);
  size_t count = (space_pos == string_view::npos) ? (str.size() - offset) : (space_pos - offset);
  
  size_t num = utils::svtol(str.substr(offset, count));
  
  offset = (space_pos == string_view::npos) ? str.size() : space_pos + 1;
  return num;
}

void Ex_23_5::Run1(ifstream& input)
{
  // return;
  cout<<"running Ex_23_5"<< '\n';
  string line;
  size_t sum = 0;
  vector<size_t> seeds;
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
  for (size_t seed : seeds)
  {
    size_t mapped_val = seed;
    for (auto& map : mappings)
    {
      for (auto& range : map)
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

struct Range {
  size_t start;
  size_t l;
};

struct CompareStart {
    bool operator()(const Mapping& a, const Mapping& b) {
      //a is destination, therfore the location, therefore the thing that needs to be the smalles
        return a.a > b.a;  // Note: > for min-heap
    }
};

bool isSmallest(size_t source_val, array<vector<Mapping>, 7>& mappings, vector<Range>& seeds) {
  for (auto it = mappings.rbegin(); it != mappings.rend(); ++it) {
    vector<Mapping>& map = *it;
    for (Mapping& range : map) {
      if(source_val >= range.a && source_val < range.a + range.range) {
        size_t normed = source_val - range.a;
        source_val = range.b + normed;
        break;
      }
    }
  }
  for (Range &seed : seeds) 
    if(source_val >= seed.start && source_val < seed.start + seed.l) return true;  
  return false;
}

void Ex_23_5::Run2(ifstream& input)
{
  cout<<"running Ex_23_5 (b)" << '\n';
  // utils::println("69323688");
  // return;
  string line;
  vector<Range> seeds;
  // getting seeds
  getline(input, line);
  string_view str(line);
  size_t end = str.find(':') + 2;
  for (size_t i = 0; end < str.size(); i++)
  {
    size_t start = popNext(end, str);
    size_t length = popNext(end, str);
    seeds.push_back(Range{start, length});
    
  }
  utils::println(seeds.size());
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
    mappings[map_i].push_back(Mapping {a, b, range});
  }
  size_t result = 0;
  bool valid = false;

  while (true)  {
    valid = isSmallest(result++, mappings, seeds);
    if(valid) break;
  }
  utils::println(result-1);
}
