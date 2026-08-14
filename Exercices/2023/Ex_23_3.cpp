#include "Ex_23_3.h"
#include "../../utils.h"
#include <charconv>
#include <tuple>

bool isSymbol(char c) {
    return c != '.' && !std::isdigit(c);
}

bool hasSymbolAround(const vector<string>& grid, size_t x, size_t y, size_t size) {
  return (x+1 < size && isSymbol(grid[y][x+1])) ||
  (y+1 < size && isSymbol(grid[y+1][x])) ||
  (x > 0 && isSymbol(grid[y][x-1])) ||
  (y > 0 && isSymbol(grid[y-1][x])) ||
  (y > 0 && x > 0 && isSymbol(grid[y-1][x-1])) ||
  (y+1 < size && x+1 < size && isSymbol(grid[y+1][x+1])) ||
  (y > 0 && x+1 < size && isSymbol(grid[y-1][x+1])) ||
  (y+1 < size && x > 0 && isSymbol(grid[y+1][x-1]));

}

void Ex_23_3::Run1(ifstream& input)
{
  return;
  string line;
  long long sum = 0;
  vector<string> grid;
  while (getline(input, line)) {
    grid.push_back(line);
  }
  // go through numbers
  // for each digit look for neighbours to check for symbols
  // while building the number
  // if finds symbol, add to sum
  size_t size = line.size();
  vector<char> num_chars;
  for (size_t y = 0; y < size; y++)
  {
    num_chars.clear();
    bool foundSymbol=false;
    for (size_t x = 0; x < size; x++)
    {
      char c = grid[y][x];
      bool isDigit = std::isdigit(c);
      if(isDigit) {
        num_chars.push_back(c);
        // check neighbors
        if(!foundSymbol && hasSymbolAround(grid, x,y,size)){
          foundSymbol = true;
        }
      }
      if(!isDigit || x == size-1)
      {
        if(foundSymbol){
          int num;
          auto [ptr, ec] = std::from_chars(num_chars.data(), num_chars.data() + num_chars.size(), num);
          sum += num;
        }
        foundSymbol = false;
        num_chars.clear();
      } 
    }
  }
  utils::println(sum);
}

void getIndeces(const vector<string>& grid, size_t x, size_t y, size_t size, vector<tuple<size_t, size_t>>& res) {
  
  if (x+1 < size && isdigit(grid[y][x+1])) res.push_back(tuple(y, x+1));
  if (y+1 < size && isdigit(grid[y+1][x])) res.push_back(tuple(y+1, x));
  if (x > 0 && isdigit(grid[y][x-1])) res.push_back(tuple(y, x-1));
  if (y > 0 && isdigit(grid[y-1][x])) res.push_back(tuple(y-1, x));
  if (y > 0 && x > 0 && isdigit(grid[y-1][x-1])) res.push_back(tuple(y-1, x-1));
  if (y+1 < size && x+1 < size && isdigit(grid[y+1][x+1])) res.push_back(tuple(y+1, x+1));
  if (y > 0 && x+1 < size && isdigit(grid[y-1][x+1])) res.push_back(tuple(y-1, x+1));
  if (y+1 < size && x > 0 && isdigit(grid[y+1][x-1])) res.push_back(tuple(y+1, x-1));

}

// go through gears
// for each gear look for neighbours to check for numbers
// add grid indeces of found numbers in vector
// check vec.len() == 2
// if not continue;
// else for each index
// find leftmost digit 
// check if already found it in case the same number in multiple neighbouring cells
// if not then convert vec to number and add to vector
// when all indeces are checked. see if vector has length of two
// multiply nums and add to sum
void Ex_23_3::Run2(ifstream& input)
{
  string line;
  long long sum = 0;
  vector<string> grid;
  while (getline(input, line)) {
    grid.push_back(line);
  }

  size_t size = line.size();
  vector<char> num_chars;
  vector<tuple<size_t, size_t>> indeces;
  vector<tuple<size_t, size_t>> start_points;
  vector<int> neighbours;
  
  for (size_t y = 0; y < size; y++)
  {
    for (size_t x = 0; x < size; x++)
    {
      char c = grid[y][x];
      bool is_gear = c == '*';
      if(!is_gear) continue;
      indeces.clear();
      neighbours.clear();
      start_points.clear();

      getIndeces(grid, x, y, size, indeces);
      for (auto &&indx : indeces)
      {
        // got to outmost left
        int ix = get<1>(indx);
        int iy = get<0>(indx);
        for (; ix >= 0; ix--)
        {
          if(!isdigit(grid[iy][ix])) break;
        }
        ix++;
        auto start_point = std::tuple(iy, ix);
        // check if it already exists
        bool exists = std::find(start_points.begin(), start_points.end(), start_point) != start_points.end();
        if(exists) continue;
        start_points.push_back(start_point);
        // create char vec
        num_chars.clear();
        for (; ix < size; ix++)
        {
          if(!isdigit(grid[iy][ix])) break;
          num_chars.push_back(grid[iy][ix]);
        }
        neighbours.push_back(utils::cvtoi(num_chars));
      }
      
      if(neighbours.size() != 2) continue;
      sum += neighbours[0] * neighbours[1];
    }
  }
  utils::println(sum);
}
