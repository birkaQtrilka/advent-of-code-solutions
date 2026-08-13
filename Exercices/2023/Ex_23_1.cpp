#include "Ex_23_1.h"
#include <array>

void Ex_23_1::Run1(ifstream& input)
{
  string line;
  long long sum = 0;
  while (getline(input, line)) {
    char first = '0';
    char last = '0';
    for (size_t i = 0; i < line.size(); i++)
    {
      char c = line[i];
      if(first == '0')
      {
        if(std::isdigit(c)) {
          first = c;
          last = c;
        }
      }
      else {
        if(std::isdigit(c)) last = c;
      }
    }
    string res{first,last};
    sum += std::stoi(res);
	}

  // cout << sum;
}

char Ex_23_1::match(const std::array<string,10>& arr, const std::string_view str) {
  int i = 0;
  for (auto &&item : arr)
  {
    string_view potential_match = str.substr(0, item.size());
    if(potential_match == item) return i + '0';
    i++;
  }
  return 'z';
}

void Ex_23_1::Run2(ifstream& input)
{
  string line;
  long long sum = 0;
  std::array<string,10> map = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
  };

  while (getline(input, line)) {
    char first = '0';
    char last = '0';
    for (size_t i = 0; i < line.size(); i++)
    {
      char c = line[i];
      if(first == '0') {
        if(std::isdigit(c)) {
          first = c;
          last = c;
          // cout<<"First: " << c << '\n';

        }
        else {
          char m = match(map, string_view(line).substr(i,5));
          if(m != 'z') {
            first = m;
            last = m;
            // cout<<"First: " << m << '\n';
          }
        }
        continue;
      }
      if(std::isdigit(c)) {
        // cout<<"Looking for last: " << c << '\n';
        last = c; 
      }
      else {
        char m = match(map, std::string_view(line).substr(i,5));
        if(m != 'z') {
          // cout<<"Looking for last: " << m << '\n';
          last = m;
        }
      }
    }

    string res{first,last};
    // cout << res << '\n';
    sum += std::stoi(res);
	}

  cout << sum;
}
