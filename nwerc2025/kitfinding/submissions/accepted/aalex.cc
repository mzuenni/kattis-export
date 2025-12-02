#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

int main() {
  int h, w;
  int k, i, t;
  std::cin >> h >> w >> k >> i >> t;

  std::vector<std::string> grid(h, std::string(w, '.'));
  --k;
  grid[0][0] = 'K';
  --i;
  grid[0][1] = 'I';
  --t;
  grid[0][2] = 'T';
  for (int j = 1; j < std::max(h, w); ++j) {
    if (j < h) for (int m = 0; m < j + 2 && m < w; ++m) {
      if (t > 0) {
        --t;
        grid[j][m] = 'T';
      } else if (k > 0) {
        --k;
        grid[j][m] = 'K';
      } else if (i > 0) {
        --i;
        grid[j][m] = 'I';
      } else {}  // This should never happen.
    }
    if (j + 2 < w) for (int m = 0; m < j + 1 && m < h; ++m) {
      if (t > 0) {
        --t;
        grid[m][j + 2] = 'T';
      } else if (k > 0) {
        --k;
        grid[m][j + 2] = 'K';
      } else if (i > 0) {
        --i;
        grid[m][j + 2] = 'I';
      } else {}  // This should never happen.
    }
  }

  for (const auto& s : grid) std::cout << s << std::endl;
    
  return 0;
}
