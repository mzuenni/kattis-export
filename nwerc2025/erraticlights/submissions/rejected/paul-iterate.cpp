// @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

static const int k = 3;

static vector<int> normalize(const vector<int> &a) {
  vector<int> b;
  b.reserve(a.size());
  for (int x : a)
    if (x > 0)
      b.push_back(x);
  sort(b.begin(), b.end());
  return b;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (!(cin >> n))
    return 0;

  // Generate all integer partitions of n in nondecreasing order
  vector<vector<int>> partitions;
  vector<int> cur;
  function<void(int, int)> rec = [&](int s, int x) {
    if (s == 0) {
      partitions.push_back(cur);
      return;
    }
    while (x <= s) {
      cur.push_back(x);
      rec(s - x, x);
      cur.pop_back();
      ++x;
    }
  };
  rec(n, 1);

  // Index map for partitions
  map<vector<int>, int> idx;
  for (int i = 0; i < (int)partitions.size(); ++i)
    idx[partitions[i]] = i;

  int m = (int)partitions.size();

  // Build adjacency with multiplicities
  vector<vector<pair<int, int>>> adj(m);
  for (int i = 0; i < m; ++i) {
    const vector<int> &a = partitions[i];
    map<vector<int>, int> go; // destination partition -> count
    // stay
    go[a] += 1;
    if (!a.empty()) {
      // move to normalize([1, a[0]-1] + a[1:]) with multiplicity (k - len(a))
      vector<int> tmp;
      tmp.reserve(a.size());
      tmp.push_back(1);
      tmp.push_back(a[0] - 1);
      for (size_t t = 1; t < a.size(); ++t)
        tmp.push_back(a[t]);
      vector<int> b = normalize(tmp);
      go[b] += (k - (int)a.size());

      // for j in range(1, len(a)):
      for (size_t j = 1; j < a.size(); ++j) {
        vector<int> tmp2;
        tmp2.reserve(a.size());
        tmp2.push_back(a[0] - 1);
        tmp2.push_back(a[j] + 1);
        for (size_t t = 1; t < a.size(); ++t)
          if (t != j)
            tmp2.push_back(a[t]);
        vector<int> b2 = normalize(tmp2);
        go[b2] += 1;
      }
    }
    adj[i].reserve(go.size());
    for (auto &p : go) {
      auto it = idx.find(p.first);
      if (it != idx.end())
        adj[i].push_back({it->second, p.second});
    }
  }

  // Value iteration
  vector<double> dp(m, 0.0);
  for (int z = 0; z < 100; ++z) {
    for (int i = 0; i < m - 1; ++i) {
      double s = 0.0;
      for (auto [j, c] : adj[i])
        s += (double)c * dp[j];
      dp[i] = 1.0 + s / (double)k;
    }
  }

  string s;
  if (!(cin >> s))
    return 0;
  map<char, int> cnt;
  for (char ch : s)
    cnt[ch]++;
  vector<int> counts;
  counts.reserve(cnt.size());
  for (auto &p : cnt)
    counts.push_back(p.second);
  vector<int> a = normalize(counts);

  cout.setf(ios::fixed);
  cout << setprecision(10) << dp[idx[a]] << '\n';
  return 0;
}
