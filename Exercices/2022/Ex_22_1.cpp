#include "Ex_22_1.h"
#include "../../utils.h"

void Ex_22_1::Run1(ifstream& input)
{
  cout<<"running Ex_22_1"<< '\n';
  string line;
  long sum = 0;
  long current = 0;
  while (getline(input, line)) {
    if(line.empty()) {
      sum = max(current, sum);
      current = 0;
      continue;
    }
    current += utils::svtoi(string_view(line));
  }
  sum = max(current, sum);
  utils::println(sum);
}

void Ex_22_1::Run2(ifstream& input)
{
  cout<<"running Ex_22_1 (b)" << '\n';
  string line;
  long sum1 = 0;
  long sum2 = 0;
  long sum3 = 0;

  long current = 0;
  auto updateTop3 = [&](long val) {
    if(val >= sum1){
        sum3 = sum2;
        sum2 = sum1;
        sum1 = val;
      }else if(val >= sum2){
        sum3 = sum2;
        sum2 = val;
      } else if (val >= sum3){
        sum3 = val;
      }
  };
  while (getline(input, line)) {
    if(line.empty()) {
      updateTop3(current);
      current = 0;
      continue;
    }
    current += utils::svtoi(line);
  }
  updateTop3(current);
  utils::println(sum1+sum2+sum3);
}
