#include "Ex_25_11.h"
#include <unordered_map>
#include "../../utils.h"

struct Connections {
  vector<string> paths;
  int ends;
};
// assuming input doesn't cycle
int FoundOut(const string& path, unordered_map<string, Connections>& map) {
  Connections& val = map[path];
  if(val.paths[0] == "out") {
    val.ends = 1;
    return 1;
  }
  if(val.ends != -1) return val.ends;
  val.ends = 0;
  for (string& p: val.paths) {
    val.ends += FoundOut(p, map);
  }

  return val.ends;
}
// might need to start from outs to you? could be the same issue if it cycles

void Ex_25_11::Run1(ifstream& input)
{
  return;
  cout<< "running Ex_25_11"<< '\n';
  string line;
  long long sum = 0;
  unordered_map<string, Connections> connections;

  auto isNotSpace = [](unsigned char c) { 
    return !std::isspace(c); 
  };

  while (getline(input, line)) {
    string_view str(line);
    size_t offset = str.find(':');
    string_view key = str.substr(0, offset);
    offset += 2;
    vector<string> paths;
    while(offset < str.size()){
      auto res = utils::popNextStr(offset, str, isNotSpace);
      paths.push_back(string(res));
    }
    connections.emplace(key, Connections {paths, -1});
  }

  sum = FoundOut("you", connections);
  utils::println(sum);  
}

struct Memoized {
  long long ab;
  long long a;
  long long b;
  long long total;
};

struct Connections2 {
  vector<string> paths;
  Memoized mem;
};


Memoized FoundOut2(const string& path, unordered_map<string, Connections2>& map) {
  Connections2& val = map[path];
  if(val.paths[0] == "out") {
    val.mem.total = 1;
    return val.mem;
  }
  if(val.mem.total != -1) return val.mem;
  val.mem.total = 0;
  bool isA = path == "fft";
  bool isB = path == "dac";
  for (const string& p: val.paths) {
    Memoized found = FoundOut2(p, map);
    val.mem.total += found.total;
    val.mem.a += found.a;
    val.mem.b += found.b;
    val.mem.ab += found.ab;
    
  }
  val.mem.a += isA * val.mem.total ;
  val.mem.b += isB * val.mem.total ;
  if(isA) {
    val.mem.ab = val.mem.b;
  } else if(isB) {
    val.mem.ab = val.mem.a;
  }
  return val.mem;
}
void Ex_25_11::Run2(ifstream& input)
{
  cout<<"running Ex_25_11 (b)" << '\n';
  
  string line;
  unordered_map<string, Connections2> connections;

  auto isNotSpace = [](unsigned char c) { 
    return !std::isspace(c); 
  };

  while (getline(input, line)) {
    string_view str(line);
    size_t offset = str.find(':');
    string_view key = str.substr(0, offset);
    offset += 2;
    vector<string> paths;
    while(offset < str.size()){
      auto res = utils::popNextStr(offset, str, isNotSpace);
      paths.push_back(string(res));
    }
    connections.emplace(key, Connections2 {paths, Memoized {0,0,0,-1}});
  }

  Memoized found = FoundOut2("svr", connections);
  utils::println(found.ab);  
}
