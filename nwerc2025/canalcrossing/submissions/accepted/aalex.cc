#include <iostream>
#include <utility>
#include <vector>

std::vector<int> parity;
std::vector<std::vector<std::pair<int, int>>> streets;

long long dfs(int node, int parent) {
  long long w = 0;
  for (auto [i, j] : streets[node]) {
    if (i == parent) continue;
    w += dfs(i, node);
    if (parity[i]) w += j;
    parity[node] ^= parity[i];
  }
  return w;
}

int main() {
  int n;
  std::cin >> n;
  parity.resize(n);
  streets.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b, w;
    std::cin >> a >> b >> w;
    --a;
    --b;
    streets[a].emplace_back(b, w);
    streets[b].emplace_back(a, w);
  }

  int m;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    --a;
    --b;
    parity[a] = !parity[a];
    parity[b] = !parity[b];
  }
  
  std::cout << dfs(0, -1) << std::endl;

  return 0;
}
