#include <iostream>
#include <utility>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  long sum_a = 0, sum_b = 0;
  std::vector<std::pair<int, int>> ab(n);
  for (auto& [a, b] : ab) {
    std::cin >> a >> b;
    sum_a += a;
    sum_b += b;
  }

  int k = 0;
  while (k < n) {
    if (sum_b - (sum_a - ab[k].first) <= ab[k].second) break;
    ++k;
  }

  if (k < n) {
    std::cout << k + 1 << std::endl;
  } else {
    std::cout << "impossible" << std::endl;
  }

  return 0;
}
