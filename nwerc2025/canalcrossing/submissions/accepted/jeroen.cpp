#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, m;
vector<vector<pair<int,int>>> adj, bridges;

long long answer = 0;

int dfs(int i, int parent) {
  int parity = bridges[i].size() % 2;

  for(auto it = adj[i].begin(); it != adj[i].end(); it++) {
    if(it->first == parent) continue;
    int rec = dfs(it->first, i);
    if(rec != 0) answer += it->second;
    parity ^= rec;
  }

  return parity;
}

int main() {
  cin >> n;
  adj = vector<vector<pair<int,int>>>(n);
  for(int i = 0; i < n - 1; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    adj[a-1].push_back(pair<int,int>(b-1,w));
    adj[b-1].push_back(pair<int,int>(a-1,w));
  }

  cin >> m;
  bridges = vector<vector<pair<int, int>>>(n);
  for(int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    bridges[a-1].push_back(pair<int,int>(b-1,i));
    bridges[b-1].push_back(pair<int,int>(a-1,i));
  }

  dfs(0, -1);

  cout << answer << endl;

  return 0;
}
