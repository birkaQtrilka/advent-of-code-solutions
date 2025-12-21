#include "Ex_10.h"
#include <regex>
#include <sstream>
#include <queue>

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

void Ex_10::Run1(ifstream& input)
{
	string line;
	int total = 0;
	while(getline(input, line))
	{
		total += AnalyzeLine(line);
		//cout << endl << "===================" << endl << endl;
  }
	cout << "Ex_10: " << total << endl;
}
struct Combination {
  vector<uint32_t> buttons;
  int start;
  uint32_t result;
	//vector<int> buttonIndexes_debug;
};
int Ex_10::AnalyzeLine(const string& line)
{
  uint32_t target = 0;
  vector<uint32_t> round;
  //cout << "Target: " << endl;
  ForEachContent(line, "[", "]", [&](string r) {
    for (size_t i = 0; i < r.size(); i++) {
      if (r[i] == '#') Toggle(target, i);
    }
    //cout << ToBitString(target) << endl;
    });
  //cout << "Buttons: " << endl;

  ForEachContent(line, "(", ")", [&](string r) {
    round.push_back(0);
    GetNumber(r, [&](int n) {
      Toggle(round.back(), n);
    });
    //cout << ToBitString(round.back()) << " : " << round.back() << endl;
    });
  // use bfs 
  queue<Combination> q;

  q.push({ {}, 0, 0/*, {} */});
  while (!q.empty()) {
    Combination node = q.front();
    q.pop();
    uint32_t guess = node.result ^ target;

		string nodeStr = ToBitString(node.result);
		string guessStr = ToBitString(guess);

    for (int i = node.start; i < round.size(); i++) {
      if ((node.result ^ round[i]) == target) {
        /*cout << "FOUND with buttons: ";
        for (auto& x : node.buttonIndexes_debug){
					cout << x << " ";
        }
				cout << i << endl;
				cout << "Result: " << endl << ToBitString(node.result ^ round[i]) << endl;*/
        //cout  << node.buttons.size()
				return node.buttons.size() + 1;
      }
			vector<uint32_t> copy = node.buttons;
			//vector<int> copy_indexes = node.buttonIndexes_debug;
			copy.push_back(round[i]);
      //copy_indexes.push_back(i);
			uint32_t r = node.result ^ round[i];

			//string rStr = ToBitString(r);
      
      q.push({ copy, i + 1, r/*, copy_indexes*/ });
    }
  }
	return 0;
}

void Ex_10::Run2(ifstream& input)
{
}

void Ex_10::ForEachContent(
  const string& line,
  const string& s,
  const string& e,
  const function<void(const string&)>& callback
)
{
  // Escape end delimiter for character class
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