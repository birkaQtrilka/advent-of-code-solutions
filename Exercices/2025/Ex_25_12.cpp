#include "Ex_25_12.h"
#include <array>
#include "../../utils.h"

struct Spot {
  int w;
  int h;
  vector<int> presents;
};

struct Shape {
  array<array<bool, 3>, 3> grid;
};

vector<Shape> ParseShapes(ifstream& input, string& line) {
  vector<Shape> shapes;
  shapes.reserve(6);
  while (getline(input, line)) {
    if(line[1] != ':') break; // end of phase 1
    getline(input, line);
    int y = 0;
    array<array<bool, 3>, 3> grid;
    while(!line.empty()) {
      for (size_t x = 0; x < 3; x++) {
        grid[y][x] = (line[x] == '#');
      }
      y++;
      getline(input, line);
    }
    shapes.push_back(Shape { move(grid) });
  }
  return shapes;
}

vector<Spot> ParseSpots(ifstream& input, string& line) {
  vector<Spot> spots;
  do {
    string_view str(line);
    size_t xIndex = str.find('x');
    size_t cIndex = str.find(':');
    int w = utils::svtoi(str.substr(0, xIndex));
    int h = utils::svtoi(str.substr(xIndex + 1, cIndex - xIndex - 1));
    size_t offset = cIndex + 2;
    vector<int> presents;
    presents.reserve(6);
    while (offset < line.size()) {
      int amount = utils::popNext(offset, str);
      presents.push_back(amount);
    }
    spots.push_back(Spot { w, h, move(presents)});
  } while (getline(input, line)); 

  return spots;
}

void Ex_25_12::Run1(ifstream& input)
{
  cout<<"running Ex_25_12"<< '\n';
  string line;
  long long sum = 0;
  vector<Shape> shapes = ParseShapes(input, line);
  vector<Spot> spots = ParseSpots(input, line);


}

void Ex_25_12::Run2(ifstream& input)
{
  cout<<"running Ex_25_12 (b)" << '\n';
  string line;
  long long sum = 0;
  while (getline(input, line)) {
  }
}
