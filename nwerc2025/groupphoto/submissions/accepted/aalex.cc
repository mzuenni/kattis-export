#include <algorithm>
#include <iostream>
#include <vector>

struct ab {
  int a0, b0;
  int a1, b1;
};

int main() {
  int n;
  std::cin >> n;

  std::vector<int> u(n);
  for (int& i : u) {
    std::cin >> i;
    --i;
  }

  std::vector<ab> w;
  for (int i = 0; i < n; ++i) {
    if (int k = u[i] - i; 0 <= k && k < n - i) {
      w.emplace_back(i, k, i + 1, k);
    }
    if (int k = u[i] - (n - i - 1); 0 <= k && k <= i) {
      w.emplace_back(k, n - i - 1, k, n - i);
    }
  }
  std::sort(w.begin(), w.end(), [](const ab& p, const ab& q) {
    if (p.b0 != q.b0) return p.b0 < q.b0;
    if (bool s = p.b0 != p.b1, t = q.b0 != q.b1; s != t) return s < t;
    return p.b0 == p.b1 ? p.a0 < q.a0 : q.a0 < p.a0;
  });

  std::vector<int> lis;
  for (const auto& i : w) {
    auto it = std::upper_bound(lis.begin(), lis.end(), i.a0);
    if (it == lis.end()) {
      lis.push_back(i.a1);
    } else {
      *it = i.a1;
    }
  }

  std::cout << n - lis.size() << std::endl;

  return 0;
}
