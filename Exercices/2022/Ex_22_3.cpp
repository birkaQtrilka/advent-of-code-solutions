#include "Ex_22_3.h"
#include <algorithm> 
#include "../../utils.h"

// sort then compare?
// can the same item appear twice?
// if I sort by storing indeces instead of rearranging the line it would be faster cuz only one allocation
// then I can check if 

void Ex_22_3::Run1(ifstream& input)
{
  cout<<"running Ex_22_3"<< '\n';
  string line;
  long long sum = 0;
  while (getline(input, line)) {
    size_t half = line.size() / 2;
    string l1 = line.substr(0, half);
    string l2 = line.substr(half, line.size() - half);
    sort(l1.begin(), l1.end());
    sort(l2.begin(), l2.end());

    // check for match 
    int j = 0;
    char curr = '!';
    for (size_t i = 0; i < l1.size(); i++) {
      if(curr == l1[i]) continue;
      char curr = l1[i];
      while(l2[j] <= curr && j < l2.size()) {
        if(l2[j] == curr) {
          // cout << "match:  " << curr << '\n';
          if(curr > 96) {
            sum += curr + 1 - 'a';
            // utils::println(curr+1 - 'a');
          }else {
            sum += curr + 27 - 'A';
            // utils::println(curr+27 - 'A');
          }
          while(l2[j] == curr && j < l2.size()) j++;
          break;
        }
        j++;
      }

    }
    
  }
  utils::println(sum);
}

void Ex_22_3::Run2(ifstream& input)
{
  cout<<"running Ex_22_3 (b)" << '\n';
  string line;
  long long sum = 0;
  while (getline(input, line)) {

  }
}
