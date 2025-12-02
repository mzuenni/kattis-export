#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct query {
  int n;
  int l;
  int r;
  bool key;
};

struct event {
  int t;
  int q1;
};

int main() {
  int n, k, q;
  std::cin >> n >> k >> q;

  std::vector<query> qs(q);
  for (auto& [n, l, r, key] : qs) std::cin >> n >> l >> r;

  std::vector<event> es(2 * q);
  for (int i = 0; i < q; ++i) {
    es[2 * i].t = qs[i].l;
    es[2 * i].q1 = -(i + 1);
    es[2 * i + 1].t = qs[i].r;
    es[2 * i + 1].q1 = i + 1;
  }
  std::sort(es.begin(), es.end(), [](const auto& a, const auto& b) {
    return a.t < b.t;
  });

  for (int i = 0, m = n; i < es.size(); ++i) {
    if (es[i].q1 < 0) {
      --m;
    } else {
      qs[es[i].q1 - 1].key = m == 0;
      ++m;
    }
  }

  bool possible = true;
  for (int i = 0, j = k; i < es.size(); ++i) {
    if (es[i].q1 < 0) {
      if (qs[-es[i].q1 - 1].key) {
        possible = j > 0;
        if (!possible) break;
        --j;
      }
    } else {
      if (qs[es[i].q1 - 1].key) {
        ++j;
      }
    }
  }

  if (possible) {
    for (const auto& i : qs) std::cout << (i.key ? '1' : '0');
    std::cout << std::endl;
  } else {
    std::cout << "impossible" << std::endl;
  }

  return 0;
}
