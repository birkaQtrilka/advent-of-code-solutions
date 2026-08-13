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

char Ex_23_1::match(const std::array<string_view,10>& arr, const std::string_view str) {
  for (size_t i = 0; i < arr.size(); i++) {
    if(str.substr(0, arr[i].size()) == arr[i]) return i + '0';
  }
  return '\0';
}

void Ex_23_1::Run2(ifstream& input)
{
  string line;
  long long sum = 0;
  std::array<string_view,10> map = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
  };

  while (getline(input, line)) {
    char first = '\0';
    char last = '\0';
    for (size_t i = 0; i < line.size(); i++)
    {
      char c = line[i];
      char current_digit = '\0';
            
      if (std::isdigit(c)) {
        current_digit = c;
      } 
      else {
        current_digit = match(map, string_view(line).substr(i));
      }
      if(current_digit != '\0') {
        if(first == '\0'){
          first = current_digit;
        }
        last = current_digit;
      }
    }
    if (first != '\0' && last != '\0') 
      sum += (first - '0') * 10 + (last - '0');
	}

  cout << sum;
}
