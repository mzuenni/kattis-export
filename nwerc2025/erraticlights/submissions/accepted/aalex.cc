#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

constexpr int MAXN = 100;

double expect[MAXN + 1][MAXN + 1][MAXN + 1];

double get(int a, int b, int c) {
  int ma = std::max(std::max(a, b), c);
  int mi = std::min(std::min(a, b), c);
  b = a + b + c - ma - mi;
  a = ma;
  c = mi;

  if (b == 0 && c == 0) return 0.0;
  if (expect[a][b][c] != 0) return expect[a][b][c];
  if (c == 0) return expect[a][b][c] = 3 + get(a + 1, b - 1, 0);
  return expect[a][b][c] = 1.5 + .5 * get(a + 1, b, c - 1) + .5 * get(a, b + 1, c - 1);
}

int main() {
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  std::cout << std::setprecision(20)
            << get(std::count(s.begin(), s.end(), 'r'),
                   std::count(s.begin(), s.end(), 'g'),
                   std::count(s.begin(), s.end(), 'b'))
            << std::endl;

  return 0;
}
