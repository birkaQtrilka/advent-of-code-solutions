#include "Ex_25_11.h"
#include <unordered_map>
#include "../../utils.h"

bool isNotSpace(unsigned char c) { 
  return !std::isspace(c); 
};

int getId(const string& name, unordered_map<string, int>& nameToId) {
  if (nameToId.find(name) == nameToId.end()) {
    int newId = nameToId.size();
    nameToId[name] = newId;
  }
  return nameToId[name];
};

int FoundOut(int u, vector<int>& memo, const vector<vector<int>>& adj, int outID) {
  if(u == outID) {
    memo[u] = 1;
    return 1;
  }
  if(memo[u] != -1) return memo[u];
  int res = 0;
  for (int p: adj[u]) {
    res += FoundOut(p, memo, adj, outID);
  }

  return memo[u] = res;
}

void Ex_25_11::Run1(ifstream& input)
{
  cout<< "running Ex_25_11"<< '\n';
  string line;
  long long sum = 0;
  unordered_map<string, int> nameToId;
  vector<vector<int>> adj;

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
    int u = getId(string(key), nameToId);
    if (u >= adj.size()) adj.resize(u + 1);

    for (const string& p_name : paths) {
      adj[u].push_back(getId(p_name, nameToId));
    }
  }

  vector<int> memoized(nameToId.size(), -1);
  int youID = nameToId["you"];
  int outID = nameToId["out"]; 
  sum = FoundOut(youID, memoized, adj, outID);
  utils::println(sum);  
}

struct Memoized {
  long long ab;
  long long a;
  long long b;
  long long total;
};

struct Context {
    int startId;
    int fftId;
    int dacId;
    int outId;
};

Memoized FoundOut2(int u, const vector<vector<int>>& adj, vector<Memoized>& memo, const Context& ctx) {
  if (u == ctx.outId) {
    return {0, 0, 0, 1}; // total = 1
  }
    
  if (memo[u].total != -1) return memo[u];
  Memoized res = {0, 0, 0, 0};

  bool isA = u == ctx.fftId;
  bool isB = u == ctx.dacId;

  for (int p: adj[u]) {
    Memoized found = FoundOut2(p, adj, memo, ctx);
    res.total += found.total;
    res.a += found.a;
    res.b += found.b;
    res.ab += found.ab;
    
  }
  if(isA) {
    res.ab += res.b;
    res.a = res.total;
  } else if(isB) {
    res.ab += res.a;
    res.b = res.total;
  }
  return memo[u] = res;
}
void Ex_25_11::Run2(ifstream& input)
{
  cout<<"running Ex_25_11 (b)" << '\n';
  unordered_map<string, int> nameToId;

  string line;
  vector<vector<int>> adj; 

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
    int u = getId(string(key), nameToId);
    if (u >= adj.size()) adj.resize(u + 1);

    for (const string& p_name : paths) {
      adj[u].push_back(getId(p_name, nameToId));
    }

  }

  Context ctx;
  ctx.startId = nameToId["svr"];
  ctx.fftId   = nameToId["fft"];
  ctx.dacId   = nameToId["dac"];
  ctx.outId   = nameToId["out"];

  vector<Memoized> memo(nameToId.size(), {0, 0, 0, -1});

  Memoized result = FoundOut2(ctx.startId, adj, memo, ctx);
  utils::println(result.ab);
}
