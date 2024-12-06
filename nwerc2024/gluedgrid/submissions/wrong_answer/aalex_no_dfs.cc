#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr int IGNORE = '#';
constexpr int UNSEEN = '.';
constexpr int INITIALISED = ',';
constexpr int TWICE = ';';
constexpr int SEEN = ':';
constexpr int CHECK = '!';

constexpr std::pair<int, int> DELTAS[] = {
  {-1, 0},
  {0, -1},
  {0, 1},
  {1, 0},
};

int h, w;
std::vector<std::string> status(h);
std::vector<std::vector<int>> labels;

std::vector<std::vector<int>> dists;

bool inside(int x, int y) {
  return 0 <= x && x < h && 0 <= y && y < w;
}

bool inside4(int x, int y) {
  return inside(x, y) && inside(x + 1, y + 1);
}

bool any4(int x, int y, char c) {
  return status[x][y] == c
      || status[x][y + 1] == c
      || status[x + 1][y] == c
      || status[x + 1][y + 1] == c;
}

bool all4(int x, int y, char c) {
  return status[x][y] == c
      && status[x][y + 1] == c
      && status[x + 1][y] == c
      && status[x + 1][y + 1] == c;
}

bool none4(int x, int y, char c) {
  return status[x][y] != c
      && status[x][y + 1] != c
      && status[x + 1][y] != c
      && status[x + 1][y + 1] != c;
}

std::vector<std::vector<int>> getdists() {
  std::vector<std::vector<int>> ds(h, std::vector<int>(w));

  std::queue<std::pair<int, int>> bfsq;
  status[h - 1][w - 1] = INITIALISED;
  ds[h - 1][w - 1] = 0;
  bfsq.emplace(h - 1, w - 1);
  while (!bfsq.empty()) {
    auto [x, y] = bfsq.front();
    bfsq.pop();
    for (auto [dx, dy] : DELTAS) {
      int x2 = x + dx, y2 = y + dy;
      if (!inside(x2, y2)) continue;
      if (status[x2][y2] != UNSEEN) continue;

      status[x2][y2] = INITIALISED;
      ds[x2][y2] = ds[x][y] + 1;
      bfsq.emplace(x2, y2);
    }
  }

  return ds;
}

std::set<std::pair<int, int>> getcomp(int x0, int y0) {
  std::set<std::pair<int, int>> comp;

  std::queue<std::pair<int, int>> bfsq;
  status[x0][y0] = TWICE;
  bfsq.emplace(x0, y0);
  comp.emplace(x0, y0);
  comp.emplace(x0, y0 + 1);
  comp.emplace(x0 + 1, y0);
  comp.emplace(x0 + 1, y0 + 1);

  while (!bfsq.empty()) {
    auto [x, y] = bfsq.front();
    bfsq.pop();
    for (auto [dx, dy] : DELTAS) {
      int x2 = x + dx, y2 = y + dy;
      if (!inside4(x2, y2)) continue;
      if (!none4(x2, y2, IGNORE)) continue;
      if (status[x2][y2] != INITIALISED) continue;

      status[x2][y2] = TWICE;
      bfsq.emplace(x2, y2);
      comp.emplace(x2, y2);
      comp.emplace(x2, y2 + 1);
      comp.emplace(x2 + 1, y2);
      comp.emplace(x2 + 1, y2 + 1);
    }
  }

  auto mit = comp.begin();
  for (auto it = comp.begin(); it != comp.end(); ++it) {
    if (dists[it->first][it->second] < dists[mit->first][mit->second]) {
      mit = it;
    }
  }
  comp.erase(mit);

  return comp;
}

bool iseven(int x0, int y0) {
  auto comp = getcomp(x0, y0);
// for (const auto& xy : comp) std::cout << xy.first << ',' << xy.second << ' ';
// std::cout << "0:" << x0 << ',' << y0 << std::endl;
  for (auto it : comp) status[it.first][it.second] = CHECK;

  bool even = true;
  for (auto it : comp) {
    auto [x, y] = it;
    if (status[x][y] != CHECK) continue;
    do {
      if (status[x][y] != CHECK) return false;
      status[x][y] = SEEN;
      even = !even;
      int t = labels[x][y] - 1;
      x = t / w;
      y = t % w;
    } while (x != it.first || y != it.second);
    even = !even;
  }

  return even;
}

bool issolvable() {
  dists = getdists();

  for (int i = 0; i + 1 < h; ++i) {
    for (int j = 0; j + 1 < w; ++j) {
      if (!all4(i, j, INITIALISED)) continue;
      if (!iseven(i, j)) return false;
    }
  }

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (status[i][j] != INITIALISED) continue;
      if ((i * w + j + 1) % (h * w) != labels[i][j]) return false;
    }
  }

  return true;
}

int main() {
  std::cin >> h >> w;
  status.resize(h);
  for (auto& s : status) std::cin >> s;
  labels.resize(h);
  for (auto& v : labels) {
    v.resize(w);
    for (auto& i : v) std::cin >> i;
  }

  std::cout << (issolvable() ? "possible" : "impossible") << std::endl;

  return 0;
}
