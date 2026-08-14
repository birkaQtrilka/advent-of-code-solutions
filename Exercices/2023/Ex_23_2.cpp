#include "Ex_23_2.h"
#include <array>
#include <charconv>

int svtoi(string_view str) {
  int i;
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), i);
  return i; 
}



template<typename... Args>
void println(Args... args) {
    ((std::cout << args << ' '), ...) << '\n';
}

void Ex_23_2::Run1(ifstream& input)
{
  string line;
  int sum = 0;
  int id = 0;
  while (getline(input, line)) {
    string_view str(line);
    size_t end = line.find(':');
    id++;

    long r = 0;
    long g = 0;
    long b = 0;
    bool correct = true;
    while(end < str.size()) {
      end+=2;
      size_t space_pos = str.find(' ', end);
      int count = space_pos - end;

      int num = svtoi(str.substr(end, count));
      end+=count;
      switch (str[end])
      {
      case 'r': r=num; end+= 3;break;
      case 'g': g=num; end+= 5;break;
      case 'b': b=num; end+= 4;break;
      default:break;
      }

      if(r > 12 || g > 13 || b > 14) {
        correct = false;
        break;
      }      
    } 
    sum += correct * id;
  }
  println(sum);
}

void Ex_23_2::Run2(ifstream& input)
{
  string line;
  long long sum = 0;
  int id = 0;
  while (getline(input, line)) {
    string_view str(line);
    size_t end = line.find(':');
    id++;

    int r = -9999999;
    int g = -9999999;
    int b = -9999999;
    while (end < str.size()) {
      end+=2;
      size_t space_pos = str.find(' ', end);
      int count = space_pos - end;

      int num = svtoi(str.substr(end, count));
      end+=count;
      switch (str[end])
      {
      case 'r': r=std::max(num, r); end+= 3;break;
      case 'g': g=std::max(num, g); end+= 5;break;
      case 'b': b=std::max(num, b); end+= 4;break;
      default:break;
      }

    } 
    sum += r*g*b;
  }
  println(sum);
}
