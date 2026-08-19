#include "Ex_22_2.h"
#include "../../utils.h"

// 0: Rock, 1: Paper, 2: Scissors

void Ex_22_2::Run1(ifstream& input)
{
  cout << "running Ex_22_2 Part 1\n";
  string line;
  long long sum = 0;
      
  while (getline(input, line)) {
    if (line.length() < 3) continue;
    
    int op = line[0] - 'A';
    int me = line[2] - 'X';
    
    int shape_score = me + 1;
    int outcome_score = 0;
    
    if (op == me) {
      outcome_score = 3; // Draw
    } else if ((op + 1) % 3 == me) {
      outcome_score = 6; // Win
    } 

    sum += shape_score + outcome_score;
  }
      
  utils::println(sum);
}

void Ex_22_2::Run2(ifstream& input)
{
  cout << "running Ex_22_2 Part 2\n";
  string line;
  long long sum = 0;
      
  while (getline(input, line)) {
    if (line.length() < 3) continue;
    
    int op = line[0] - 'A';
    int outcome = line[2] - 'X';
    
    int outcome_score = outcome * 3;
    int me = 0;
    
    if (outcome == 1) { // Draw
      me = op;
    } else if (outcome == 2) { // Win
      me = (op + 1) % 3;
    } else { // Lose
      me = (op + 2) % 3;
    }
    
    int shape_score = me + 1;
    
    sum += shape_score + outcome_score;
  }
      
  utils::println(sum);
}