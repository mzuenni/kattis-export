#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr int DONE = '#';
constexpr int TODO = '.';
constexpr std::pair<int, int> DELTAS[] = {
  {-1, 0},
  {0, -1},
  {0, 1},
  {1, 0},
};

int h, w;
std::vector<std::string> status;
std::vector<std::vector<int>> puzzle;

auto genblocks() {
  std::vector<std::set<std::pair<int, int>>> blocks;
  std::vector<std::vector<char>> seen(h, std::vector<char>(w, false));
  std::queue<std::pair<int, int>> bfsq;

  for (int i = 0; i + 1 < h; ++i) {
    for (int j = 0; j + 1 < w; ++j) {
      if (seen[i][j]
          || status[i][j] != TODO
          || status[i][j + 1] != TODO
          || status[i + 1][j] != TODO
          || status[i + 1][j + 1] != TODO) continue;
      seen[i][j] = true;

      auto& block = blocks.emplace_back();
      block.emplace(i, j);
      block.emplace(i, j + 1);
      block.emplace(i + 1, j);
      block.emplace(i + 1, j + 1);

      for (bfsq.emplace(i, j); !bfsq.empty(); bfsq.pop()) {
        auto [x, y] = bfsq.front();
        for (auto [dx, dy] : DELTAS) {
          int x2 = x + dx, y2 = y + dy;
          if (x2 < 0 || x2 + 1 >= h || y2 < 0 || y2 + 1 >= w) continue;

          if (seen[x2][y2]
              || status[x2][y2] != TODO
              || status[x2][y2 + 1] != TODO
              || status[x2 + 1][y2] != TODO
              || status[x2 + 1][y2 + 1] != TODO) continue;
          seen[x2][y2] = true;

          block.emplace(x2, y2);
          block.emplace(x2, y2 + 1);
          block.emplace(x2 + 1, y2);
          block.emplace(x2 + 1, y2 + 1);

          bfsq.emplace(x2, y2);
        }
      }
    }
  }

  return blocks;
}

void removemins(auto& blocks) {
  std::vector<std::vector<int>> dist(h, std::vector<int>(w, -1));
  std::queue<std::pair<int, int>> bfsq;

  dist[h - 1][w - 1] = 0;
  for (bfsq.emplace(h - 1, w - 1); !bfsq.empty(); bfsq.pop()) {
    auto [x, y] = bfsq.front();
    for (auto [dx, dy] : DELTAS) {
      int x2 = x + dx, y2 = y + dy;
      if (x2 < 0 || x2 >= h || y2 < 0 || y2 >= w) continue;

      if (dist[x2][y2] >= 0 || status[x2][y2] != TODO) continue;
      dist[x2][y2] = dist[x][y] + 1;

      bfsq.emplace(x2, y2);
    }
  }

  for (auto& block : blocks) {
    std::pair<int, int> min{-1, -1};
    for (auto xy : block) {
      if (min.first < 0
          || dist[min.first][min.second] > dist[xy.first][xy.second]) {
        min = xy;
      }
    }
    block.erase(min);
  }
}

bool issolvable() {
  auto blocks = genblocks();
  removemins(blocks);

  for (const auto& block : blocks) {
    bool even = true;
    for (auto xy : block) {
      auto [x, y] = xy;
      if (status[x][y] != TODO) continue;
      do {
        if (!block.contains({x, y})) return false;
        status[x][y] = DONE;
        even = !even;
        int p = puzzle[x][y] - 1;
        x = p / w;
        y = p % w;
      } while (x != xy.first || y != xy.second);
      even = !even;
    }
    if (!even) return false;
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (status[i][j] != TODO) continue;
      if ((i * w + j + 1) % (h * w) != puzzle[i][j]) return false;
    }
  }

  return true;
}

int main() {
  std::cin >> h >> w;
  status.resize(h);
  for (auto& s : status) std::cin >> s;
  puzzle.resize(h);
  for (auto& v : puzzle) {
    v.resize(w);
    for (auto& i : v) std::cin >> i;
  }

  std::cout << (issolvable() ? "possible" : "impossible") << std::endl;

  return 0;
}
