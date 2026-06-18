#include <bits/stdc++.h>
#include <unistd.h>
#include <cassert>

using namespace std;
using uint = unsigned;
using ll = long long;
using ull = unsigned long long;

#define endl '\n'

const size_t max_n = 3000;
const ll mod = 998244353;

struct Mod {
  ll x;
  Mod(ll xx) : x(xx) {}

  static constexpr inline auto inverses = []() {
    array<ll, max_n + 1> invs{};
    invs[1] = 1;
    for (ll i = 2; i < ssize(invs); ++i)
      invs[i] = 1LL * (mod - (mod / i)) * invs[mod % i] % mod;
    return invs;
  }();

  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  auto &operator+=(Mod b) {
    *this = *this + b;
    return *this;
  }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  auto &operator-=(Mod b) {
    *this = *this - b;
    return *this;
  }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  auto &operator*=(Mod b) {
    *this = *this * b;
    return *this;
  }
  Mod operator/(Mod b) { return *this * invert(b); }
  auto &operator/=(Mod b) {
    *this = *this / b;
    return *this;
  }
  Mod invert(Mod a) {
    assert(a.x != 0);
    return inverses.at(a.x);
  }
  Mod operator^(ll e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
};

template <typename F> struct by_key {
  F f;

  bool operator()(const auto &lhs, const auto &rhs) const { return f(lhs) < f(rhs); }
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

  // Replace year values with indices
  for (auto &[ai, bi] : cards)
    ai = year_to_index[ai], bi = year_to_index[bi];

  auto cards_by_min = cards, cards_by_max = cards;
  ranges::sort(cards_by_min,
               by_key([&](const auto &card) { return min(card.first - 1, card.second); }));
  ranges::reverse(cards_by_min);

  ranges::sort(cards_by_max,
               by_key([&](const auto &card) { return max(card.first + 1, card.second); }));

  const auto compute = [&]<typename Q>(Q _infer) {
    // dp[l][r] is expected number of cards if we use cards (a, b) with l < a < r and l <= b <= r
    auto dp = vector(N, vector(N, Q(0)));

    struct PrefixState {
      Q sum = 0;
      size_t count = 0;
      size_t next_index = 0;

      void update_from_left(size_t l, size_t r, const vector<vector<Q>> &dp,
                            const vector<pair<ll, ll>> &ordered_cards) {
        while (next_index < ordered_cards.size()) {
          const auto [a, b] = ordered_cards[next_index];
          if (!(l < a && l <= b)) {
            next_index += 1;
            continue;
          }
          if (!(a < r && b <= r)) {
            break;
          }

          sum += dp[l][a];
          count += 1;
          next_index += 1;
        }
      }

      void update_from_right(size_t l, size_t r, const vector<vector<Q>> &dp,
                             const vector<pair<ll, ll>> &ordered_cards) {
        while (next_index < ordered_cards.size()) {
          const auto [a, b] = ordered_cards[next_index];
          if (!(a < r && b <= r)) {
            next_index += 1;
            continue;
          }
          if (!(l < a && l <= b)) {
            break;
          }

          sum += dp[a][r];
          count += 1;
          next_index += 1;
        }
      }
    };

    auto prefix = vector(N, PrefixState{});
    auto suffix = prefix;

    for (size_t interval_len = 0; interval_len < N; ++interval_len) {
      for (size_t l = 0; l + interval_len < N; ++l) {
        const auto r = l + interval_len;

        prefix[l].update_from_left(l, r, dp, cards_by_max);
        suffix[r].update_from_right(l, r, dp, cards_by_min);

        assert(prefix[l].count == suffix[r].count);
        const auto count = prefix[l].count;
        if (count > 0) {
          dp[l][r] = Q(count) + prefix[l].sum + suffix[r].sum;
          dp[l][r] /= Q(count);
        }
      }
    }
    return dp.front().back();
  };

  if (n <= 8)
    cerr << "Readable answer: " << compute(double(42)) << endl;
  cout << compute(Mod(42)).x << endl;
}
