#include "Ex_22_2.h"
#include "../../utils.h"

void Ex_22_2::Run1(ifstream& input)
{
  cout<<"running Ex_22_2"<< '\n';
  string line;
  long long sum = 0;
  //-65
  while (getline(input, line)) {
    char op = line[0];
    char me = line[2];
    int op_code = op - 'A';
    int me_code = me - 'X';
    sum += me_code + 1;
    if(op_code == me_code) {
      // draw
      sum += 3;
    }
    else if((op_code == 0 && me_code == 1) || (op_code == 1 && me_code == 2) || (op_code == 2 && me_code == 0)) {
      // win
      sum += 6;
    }
    // else {
    //   // loss
    // }
  }
  utils::println(sum);
}

void Ex_22_2::Run2(ifstream& input)
{
  string line;
  long long sum = 0;
  //-65
  while (getline(input, line)) {
    char op = line[0];
    char me = line[2];
    int op_code = op - 'A';
    int me_code = me - 'X';
    sum++;
    if(me_code == 1) {
      // draw
      sum += 3 + op_code;
    }
    else if(me_code == 2) {
      // win
      sum += 6 + ((op_code + 1) % 3);
    }
    else {
      // loss
      sum += (op_code + 2) % 3;
    }
  }
  utils::println(sum);
}
