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

void Ex_25_11::Run2(ifstream& input)
{
  cout<<"running Ex_25_11 (b)" << '\n';
  string line;
  long long sum = 0;
  while (getline(input, line)) {

  }
}
