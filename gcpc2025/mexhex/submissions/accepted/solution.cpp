#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int main() {
  int n, d;
  std::map<int, std::set<int>> ps;

  std::cin >> n >> d;
  for (int i = 1; i <= n; ++i) {
    int ai;
    std::cin >> ai;
    ps[ai].insert(i);
  }

  const auto possible = [d](std::set<int> p) {
    int l = 1;
    while (!p.empty()) {
      const auto i = *p.begin();
      assert(l <= i);
      const auto first_after = p.lower_bound(i + d);
      const auto last_in = std::prev(first_after);
      const auto x = std::max(l, 1 + *last_in - d);
      assert(x <= i);
      assert(i < x + d);
      assert(x <= *last_in);
      assert(*last_in < x + d);

      const auto first_after_x = p.lower_bound(x + d);
      if (first_after_x != p.end() && *first_after_x < x + 2 * d) {
        return false;
      }

      p.erase(p.begin(), p.lower_bound(x + 2 * d));
      l = x + 2 * d;
    }

    return true;
  };

  for (int i = 0; i <= n + 1; ++i) {
    if (possible(std::move(ps[i]))) {
      std::cout << i << std::endl;
      return 0;
    }
  }

  assert(false);
}
