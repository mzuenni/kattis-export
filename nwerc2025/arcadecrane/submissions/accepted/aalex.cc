#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>

std::vector<int> rotate(std::vector<int> v, int i, int j) {
  auto u = v;
  int a = std::min(i, j);
  int b = std::max(i, j) + 3;
  for (int k = a; k < b; ++k) u[a + (k - a + j - i + b - a) % (b - a)] = v[k];
  return u;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto& k : a) std::cin >> k;

  std::vector<std::pair<int, int>> ops;
  while (a.size() > 5) {
    int pos = std::max_element(a.begin(), a.end()) - a.begin();
    if (pos < 2) {
      ops.push_back({2, 0});
      a = rotate(a, 2, 0);
      pos += 3;
    }
    ops.emplace_back(pos - 2, a.size() - 3);
    a = rotate(a, pos - 2, a.size() - 3);
    a.resize(a.size() - 1);
  }

  std::map<std::vector<int>, std::vector<std::pair<int, int>>> fin;
  fin[a].clear();
  std::queue<std::vector<int>> que;
  que.push(a);
  while (fin.find({1, 2, 3, 4, 5}) == fin.end()) {
    auto f = que.front();
    que.pop();
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        auto g = rotate(f, i, j);
        if (fin.find(g) == fin.end()) {
          fin[g] = fin[f];
          fin[g].push_back({i, j});
          que.push(g);
        }
      }
    }
  }
  ops.insert(ops.end(), fin[{1, 2, 3, 4, 5}].begin(), fin[{1, 2, 3, 4, 5}].end());

  std::cout << ops.size() << std::endl;
  for (auto [i, j] : ops) std::cout << i + 1 << ' ' << j + 1 << std::endl;

  return 0;
}
