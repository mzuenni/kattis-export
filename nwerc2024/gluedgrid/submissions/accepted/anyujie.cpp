#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

using LL = long long;

class BiconnectedComponent {
public:
  BiconnectedComponent(int _n) : 
    n(_n),
    x(_n),
    dfn(_n),
    low(_n) {}

  void Block(int a, int f, int &time) {
    dfn[a] = low[a] = time; 
    S.push(a);
    for (int i = 0; i < x[a].size(); ++i) {
      if (x[a][i] == f) continue;
      if (dfn[x[a][i]] == 0) {
        Block(x[a][i], a, ++time);
        low[a] = min(low[a], low[x[a][i]]);
        if (low[x[a][i]] >= dfn[a]) {
          vector<int> curblock;
          while (S.top() != x[a][i]) {
            curblock.push_back(S.top());
            S.pop();
          }
          curblock.push_back(S.top());
          curblock.push_back(a);
          S.pop();
          blocks.push_back(std::move(curblock));
        }
      } else {
        low[a] = min(low[a], dfn[x[a][i]]);
      }
    }
  }

  void Block() {
    int t = 1;
    Block(n - 1, n - 1, t);
  }
 
  void AddEdge(int a, int b) {
    x[a].push_back(b);
    x[b].push_back(a);
  }

  int n;
  vector<vector<int>> x;
  vector<int> dfn, low;
  stack<int> S;
  vector<vector<int>> blocks;
};


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> st(n);
  for (int i = 0; i < n; ++i) cin >> st[i];
  vector<int> x(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> x[i * m + j];
      --x[i * m + j];
    }
  }
  BiconnectedComponent bcc(n * m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (st[i][j] != '.') continue;
      if (i + 1 < n && st[i + 1][j] == '.') {
        bcc.AddEdge(i * m + j, (i + 1) * m + j);
      }
      if (j + 1 < m && st[i][j + 1] == '.') {
        bcc.AddEdge(i * m + j, i * m + j + 1);
      }
    }
  }
  bcc.Block();
  vector<bool> z(n * m);
  for (int i = 0; i < bcc.blocks.size(); ++i) {
    for (int j = 0; j + 1 < bcc.blocks[i].size(); ++j) {
      z[bcc.blocks[i][j]] = true;
    }
    for (int j = 0; j + 1 < bcc.blocks[i].size(); ++j) {
      if (!z[x[bcc.blocks[i][j]]]) {
        cout << "impossible\n";
        return 0;
      }
      z[x[bcc.blocks[i][j]]] = false;
    }
    int cnt = 0;
    for (int j = 0; j + 1 < bcc.blocks[i].size(); ++j) {
      while (x[bcc.blocks[i][j]] != bcc.blocks[i][j]) {
        ++cnt;
        swap(x[bcc.blocks[i][j]], x[x[bcc.blocks[i][j]]]);
      }
    }
    if (cnt & 1) {
      cout << "impossible\n";
      return 0;
    }
  }
  cout << "possible\n";
  return 0;
}