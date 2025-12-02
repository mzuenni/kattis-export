#include <array>
#include <iostream>
#include <vector>

constexpr std::array DENOMS = {1, 2, 5, 10, 20, 50, 100, 200, 500};
constexpr int MAXN = 10000;

int sieve[MAXN + 1];

std::vector<int> split(int n) {
  std::vector<int> v;
  if (n == 0) return v;
  if (sieve[n] > 0) {
    v.insert(v.end(), n / sieve[n], sieve[n]);
    n %= sieve[n];
    for (auto it = DENOMS.rbegin(); it != DENOMS.rend(); ++it) {
      v.insert(v.end(), n / *it, *it);
      n %= *it;
    }
  } else if (sieve[n] < 0) {
    v = split(n % -sieve[n]);
    v.insert(v.end(), n / -sieve[n], -sieve[n]);
  } else {
    // This should never happen.
  }
  return v;
}

int main() {
  int n;
  std::cin >> n;

  for (int d : DENOMS) {
    for (int i = d; i <= n; i += 2 * d) {
      for (int j = i; j <= n && j < i + d; ++j) {
        sieve[j] = d;
      }
    }
    for (int i = 2 * d; i <= n; i += 2 * d) {
      for (int j = i; j <= n && j < i + d; ++j) {
        if (sieve[j - i] != 0) {
          sieve[j] = -d;
        }
      }
    }
  }

  if (sieve[n] == 0) {
    std::cout << "splittable" << std::endl;
    return 0;
  }

  std::vector<int> v = split(n);
  std::cout << v.size() << std::endl;
  bool space = false;
  for (int d : v) {
    if (space) std::cout << ' ';
    space = true;
    std::cout << d;
  }
  std::cout << std::endl;

  return 0;
}
