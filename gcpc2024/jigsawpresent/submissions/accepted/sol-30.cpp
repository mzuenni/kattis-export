#include <bits/stdc++.h>
using namespace std;
const int C = 4'100;
const int N = 30;
const int M = 13;

map<int, pair<int, int>> vis[(2 * C + 1) * M];
pair<int, int> a[N];

void print(int x, int y) {
  cout << "no\n";
  for (int msk: {x, y}) {
    cout << __builtin_popcount(msk) << " ";
    for (int i = 0; i < N; i++) {
      if (msk >> i & 1) {
        msk ^= 1 << i;
        cout << i + 1 << " \n"[msk == 0];
      }
    }
  }
  exit(0);
}

void dfs(int x, int y, int m, int f, int mskL, int mskR) {
  if (!x && !y)
    print(mskL, mskR);
  if (m < 0 && f == 0) {
    vis[x + M * C][y] = make_pair(mskL, mskR);
    return;
  } else if (m < M && f == 1) {
    for (int s: {-1, 1}) {
      int i = s * x + M * C;
      if (i >= 0 && i < (2 * C + 1) * M && vis[i].count(s * y)) {
        auto [u, v] = vis[i][s * y];
        if (s == -1)
          swap(u, v);
        print(mskL | v, mskR | u);
      }
    }
    return;
  }
  dfs(x, y, m - 1, f, mskL, mskR);
  dfs(x + a[m].first, y + a[m].second, m - 1, f, mskL | (1 << m), mskR);
  dfs(x - a[m].first, y - a[m].second, m - 1, f, mskL, mskR | (1 << m));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n;
  n = min(n, N);
  for (int i = 0; i < n; i++) {
    cin >> a[i].second >> a[i].first;
    dfs(a[i].first, a[i].second, i - 1, i >= M, 1 << i, 0);
  }
  cout << "yes\n";
}
