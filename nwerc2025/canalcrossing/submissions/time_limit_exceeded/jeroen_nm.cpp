#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, m;
vector<vector<pair<int,int>>> adj, bridges;

long long answer = 0;

set<int> dfs(int i, int parent) {
  set<int> conn;
  for(auto it = bridges[i].begin(); it != bridges[i].end(); it++) {
    conn.insert(it->second);
  }

  for(auto it = adj[i].begin(); it != adj[i].end(); it++) {
    if(it->first == parent) continue;
    set<int> rec = dfs(it->first, i);
    if(rec.size() % 2 != 0) answer += it->second;
    for(auto r = rec.begin(); r != rec.end(); r++) {
      if(conn.contains(*r))
	conn.erase(*r);
      else
	conn.insert(*r);
    }
  }

  return conn;
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
