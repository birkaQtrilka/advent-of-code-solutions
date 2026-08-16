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
  return;
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
  for (auto it = mappings.rbegin() + 1; it != mappings.rend(); ++it) {
    vector<Mapping>& map = *it;
    for (Mapping& range : map) // check if number goes through the range and therefore mapping
    {
      if(source_val >= range.a && source_val < range.a + range.range) {
        size_t normed = source_val - range.a;
        source_val = range.b + normed;
        // if (source_val < range.b) {
        //   utils::println("overflow!!");
        // }
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
  std::priority_queue<Mapping, std::vector<Mapping>, CompareStart> lowestLocationRanges;

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
    if(map_i == 6){
      lowestLocationRanges.push(Mapping {a, b, range});
    }
  }
  // it's not seed range but location range
  // b is source
  // a is destination
  // reversed for this exercise
  size_t result = std::numeric_limits<size_t>::max();
  bool valid = false;

  Mapping mapping = lowestLocationRanges.top();
  lowestLocationRanges.pop();
  
  for (size_t i = 0; i < mapping.a + mapping.range; i++) {
    size_t source_val = i;
    result = source_val;
    if(i >= mapping.a) {
      source_val += mapping.b;
      if(i+1 >= mapping.a + mapping.range) {
        mapping = lowestLocationRanges.top(); // assuming it will never reach the end of the queue
        lowestLocationRanges.pop();
      }
    }
  
    valid = isSmallest(source_val, mappings, seeds);
    if(valid) break;
  }
  utils::println(result);
}
