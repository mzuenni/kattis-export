#include <iostream>
#include <string>
#include <utility>

using ulol = unsigned long long;

ulol nchoosek(int n, int k) {
  if (k < 0 || k > n) return 0;
  static ulol cache[65][65];
  if (cache[n][k]) return cache[n][k];
  return cache[n][k] = k == 0 || k == n
    ? 1
    : nchoosek(n - 1, k) + nchoosek(n - 1, k - 1);
}

ulol patternof(int n, int k, ulol idx) {
  if (k == 0) return 0;
  return idx < nchoosek(n - 1, k)
      ? patternof(n - 1, k, idx) << 1
      : patternof(n - 1, k - 1, nchoosek(n, k) - 1 - idx) << 1 | 1;
}

ulol indexof(int n, int k, ulol pat) {
  if (pat == 0) return 0;
  return pat & 1
      ? nchoosek(n, k) - 1 - indexof(n - 1, k - 1, pat >> 1)
      : indexof(n - 1, k, pat >> 1);
}

ulol patternof(const std::string& str) {
  ulol pat = 0;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '#') pat |= 1ull << i;
  }
  return pat;
}

std::pair<int, int> posof(ulol mask, int w) {
  int pos = 0;
  while (mask >> pos > 1) ++pos;
  return {pos / w, pos % w};
}

int main() {
  int t;
  std::cin >> t;
  while (t-- > 0) {
    ulol pat = 0;

    int h, w, k;
    std::cin >> h >> w >> k;
    for (int i = 0; i < h; ++i) {
      std::string str;
      std::cin >> str;
      pat |= patternof(str) << (i * w);
    }

    if (nchoosek(h * w, k) % 2 != 0) {
      std::cout << "risky" << std::endl;
      continue;
    }

    ulol mov = patternof(h * w, k, indexof(h * w, k, pat) ^ 1) ^ pat;
    ulol low = mov & -mov;
    auto [x0, y0] = posof(pat & low ? low : mov ^ low, w);
    auto [x1, y1] = posof(pat & low ? mov ^ low : low, w);
    std::cout << x0 + 1 << ' ' << y0 + 1 << std::endl;
    std::cout << x1 + 1 << ' ' << y1 + 1 << std::endl;
  }

  return 0;
}
