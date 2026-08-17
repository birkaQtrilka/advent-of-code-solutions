#include "Ex_23_6.h"
#include "../../utils.h"

  // (s means time, m means distance)
  // x is s 
  //   m/s ,  s                   m     m
  // v(f(x), totalTime-x) - totalDist > 0
  //   
  //   x  * (totalTime - x) - totalDist = 0
  //  -x^2 + totalTime*x - totalDist = 0;
  //  x^2 - totalTime*x + totalDist = 0;
  //  x1 = (totalTime - (totalTime^2 -4*totalDist).sqrt) / 2
  //  x2 = (totalTime + (totalTime^2 -4*totalDist).sqrt) / 2
  //  
  //  -x^2 + 7x - 9 = 0;
  //  x1 = (7 + (49 - 36).sqrt) / 2 = (7 - 13.sqrt) / 2 = 
  //  x2 = (7 + (49 - 36).sqrt) / 2 = (7 + 13.sqrt) / 2 = 

void pushToVec(vector<int>& vec, ifstream& input){
  string line;
  getline(input, line);
  string_view str(line);
  size_t offset = std::find_if(str.begin(), str.end(), 
  [](unsigned char c) { return std::isdigit(c); }) - str.begin();
  while(offset < line.size()){
    auto d = utils::popNext(offset, str);
    vec.push_back(d);
  }
};

void Ex_23_6::Run2(ifstream& input)
{
  cout<<"running Ex_23_6"<< '\n';
  long long prod = 1;
  auto combine = [&input]() {
    string line;
    getline(input, line);
    string_view str(line);
    size_t offset = std::find_if(str.begin(), str.end(), 
    [](unsigned char c) { return std::isdigit(c); }) - str.begin();
    string res;
    while(offset < line.size()){
      res += utils::popNextStr(offset, str);
    }
    return std::stod(res);
  };

  double totalTime = combine();
  double totalDist = combine();
  double disc = sqrt(totalTime * totalTime - 4 * totalDist);
  double x1 = (totalTime - disc) * 0.5;
  double x2 = (totalTime + disc) * 0.5;
  long strictMin = floor(x1 + 1.000001); 
  long strictMax = ceil(x2 - 1.000001);
  utils::println( 
  "  x1: "+ to_string(strictMin) + 
  "  x2: "+ to_string(strictMax) + 
  "  mult: " + 
  to_string(strictMax-strictMin + 1));
  prod = strictMax - strictMin + 1;
  utils::println(prod);
}


void Ex_23_6::Run1(ifstream& input)
{
  long long prod = 1;
  vector<int> times;
  vector<int> distances;

  pushToVec(times, input);
  pushToVec(distances, input);

  for (size_t i = 0; i < times.size(); i++)
  {
    double totalTime = times[i];
    double totalDist = distances[i];
    double disc = sqrt(totalTime * totalTime - 4 * totalDist);
    double x1 = (totalTime - disc) * 0.5;
    double x2 = (totalTime + disc) * 0.5;
    long strictMin = floor(x1 + 1.000001); 
    long strictMax = ceil(x2 - 1.000001);
    utils::println("i: "+ to_string(i) + 
    "   x1: "+ to_string(strictMin) + 
    "  x2: "+ to_string(strictMax) + 
    "  mult: " + 
    to_string(strictMax-strictMin + 1));
    prod *= strictMax - strictMin + 1;
  }
  utils::println(prod);
}
