#include <algorithm>
#include <array>
#include <compare>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct top10 {
  int total;
  std::array<int, 10> hits;

  std::strong_ordering operator<=>(const top10& other) const = default;
};

int main() {
  int n;
  std::cin >> n;

  std::map<std::string, top10> stats;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 10; ++j) {
      std::string name;
      std::cin >> name;
      ++stats[name].total;
      ++stats[name].hits[j];
    }
  }

  std::vector<std::string> names;
  for (const auto& [k, v] : stats) names.push_back(k);
  std::sort(names.begin(), names.end(), [&stats](const auto& a, const auto& b) {
    return stats[a] > stats[b];
  });
  if (names.size() == 1 || stats[names[0]] > stats[names[1]]) {
    std::cout << names[0] << std::endl;
  } else {
    std::cout << "tie" << std::endl;
  }

  return 0;
}
