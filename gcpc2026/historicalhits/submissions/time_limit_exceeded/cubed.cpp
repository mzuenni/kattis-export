#include <bits/stdc++.h>
#include <unistd.h>
#include <cassert>

using namespace std;
using uint = unsigned;
using ll = long long;
using ull = unsigned long long;

#define endl '\n'

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

const ll mod = 998244353;
struct Mod {
  ll x;
  Mod(ll xx) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);

  size_t n;
  cin >> n;

  vector<pair<ll, ll>> cards(n);
  map<ll, int> year_to_index;
  for (auto &[ai, bi] : cards) {
    cin >> ai >> bi;
    year_to_index[ai] = 0;
    year_to_index[bi] = 0;
  }

  {
    // We add negative and positive "infinity" so that the final dp value includes all cards
    year_to_index[-1] = 0;
    year_to_index[1e9 + 42] = 0;

    int next_index = 0;
    for (auto &[year, index] : year_to_index)
      index = next_index++;
  }
  const auto N = year_to_index.size();

  const auto compute = [&]<typename Q>(Q _infer) {
    // dp[l][r] is expected number of cards if we use cards (a, b) with l < a < r and l <= b <= r
    auto dp = vector(N, vector(N, Q(0)));

    for (size_t interval_len = 0; interval_len < N; ++interval_len) {
      for (size_t l = 0; l + interval_len < N; ++l) {
        const auto r = l + interval_len;

        size_t denominator = 0;
        for (const auto [a, b] : cards) {
          const auto a_index = year_to_index.at(a);
          const auto b_index = year_to_index.at(b);
          if (l < a_index && a_index < r && l <= b_index && b_index <= r) {
            const auto expected_if_chosen_first = Q(1) + dp[l][a_index] + dp[a_index][r];
            dp[l][r] = dp[l][r] + expected_if_chosen_first;
            denominator++;
          }
        }
        if (denominator != 0)
          dp[l][r] = dp[l][r] / Q(denominator);
      }
    }
    return dp.front().back();
  };

  if (n <= 8)
    cerr << "Readable answer: " << compute(double(42)) << endl;
  cout << compute(Mod(42)).x << endl;
}
