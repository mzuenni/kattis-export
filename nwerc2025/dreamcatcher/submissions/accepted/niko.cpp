//
// Created by niko on 5/4/25.
//

#include <cmath>
#include <iostream>
#include <utility>
#include <numeric>

using ld = long double;
using namespace std;

long long n;

ld l(long long k) {
  ld once = 2 * sinl(2 * M_PI * k / (2 * n));
  auto g = gcd(n, k);
  return once * n / g;
}

int main() {

   cin >> n;

   std::pair<ld, int> x = {0, 0};
   for (long long i = std::max(1ll, n / 2 - 10000); i < std::min(n, n/2 + 10000); i++) {
     x = max(x, {l(i), i});
   }

   cout << x.second << endl;
  return 0;
}