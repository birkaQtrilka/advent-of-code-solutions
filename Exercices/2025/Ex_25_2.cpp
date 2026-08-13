
/*Part One � Find IDs made of a repeated two-part pattern

You are given several numeric ID ranges.
An ID is considered invalid if it consists of some sequence of digits repeated exactly twice
(e.g., 55, 6464, 123123). IDs never have leading zeroes.

--> How many invalid IDs (sum of their numeric values) appear in all given ranges?

Part Two � Find IDs made of any repeated pattern (two or more times)

Now, an ID is invalid if it consists of any sequence of digits repeated at least twice
(e.g., 12341234, 123123123, 1212121212, 1111111).

--> How many invalid IDs (sum of their numeric values) appear in all given ranges under the new rules?
*/

#include "Ex_25_2.h"
#include <cmath>
#include <sstream>

void Ex_25_2::Run1(ifstream& input)
{
  string line;
  getline(input, line);

  stringstream ss(line);
  string range;
  long long count = 0;

  while (getline(ss, range, ',')) {
    size_t dashPos = range.find('-');
    string a = range.substr(0, dashPos);
    string b = range.substr(dashPos + 1);
    long long start = stoll(a);
    long long end = stoll(b);


    for (long long i = start; i <= end; i++)
    {
      string strNum = to_string(i);
      int digits = strNum.length();
      if (digits % 2 != 0) continue;
      int half = digits / 2;
      bool valid = false;
      for (size_t j = 0; j < half; j++)
      {
        if (strNum[j] != strNum[j + half]) valid = true;
      }

      if (!valid) {
        count += i;
      }
    }
  }
  cout << "Ex_25_2: " << count << endl;
}

void Ex_25_2::Run2(ifstream& input)
{
  string line;
  getline(input, line);

  stringstream ss(line);
  string range;
  long long count = 0;

  while (getline(ss, range, ',')) {
    size_t dashPos = range.find('-');
    string a = range.substr(0, dashPos);
    string b = range.substr(dashPos + 1);
    long long start = stoll(a);
    long long end = stoll(b);

    for (long long i = start; i <= end; i++)
    {
      string strNum = to_string(i);
      int digits = strNum.length();
      int half = digits / 2;
      int divisionLength = 1;
      while (divisionLength <= half) {
        if (digits % divisionLength != 0) { // digits need to be divisible
          divisionLength++;
          continue;
        }
        int divisionCount = digits / divisionLength; 
        bool invalid = true;
        for (size_t j = 0; j < divisionLength; j++) {
          char toCompare = strNum[j];

          for (size_t h = 1; h < divisionCount; h++)
          {
            if (strNum[divisionLength * h + j] != toCompare) {
              invalid = false;
              break;
            }
          }
          if (!invalid) break;
        }

        // only care about smallest division
        if (invalid) {
          count += i; 
          break;
        }

        divisionLength++;
      }
    }
  }
  cout << "Ex_25_2 (b): " << count << endl;
}
