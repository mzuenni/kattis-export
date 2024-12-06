#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;


template<class T>
auto dijkstra(int source, vector<vector<pair<int, T>>> &g) {
  int n = sz(g);
  vector<T> dist(n, numeric_limits<T>::max());
  vector<pair<int,T> > dad(n, {-1, 0});
  priority_queue<pair<T,int> > pq;
  dist[source] = 0;
  pq.emplace(0,source);
  while(!pq.empty()) {
    T d; int x;
    tie(d,x) = pq.top();
    d = -d;
    pq.pop();
    if(d > dist[x]) continue;
    for(auto [y,w] : g[x]) {
      if(dist[y] > d + w) {
        dist[y] = d + w;
        dad[y] = {x, w};
        pq.emplace(-dist[y], y);
      }
    }
  }
  return dist;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int n,m,k;
  cin>>n>>m>>k;
  vector<vector<pair<int,ll>>> g(n);
  rep(i,0,m) {
    int x,y;
    ll z;
    cin>>x>>y>>z;
    --x,--y;
    g[x].emplace_back(y,z);
    g[y].emplace_back(x,z);
  }
  auto d0 = dijkstra(0,g);
  auto dn = dijkstra(n-1,g);

  vector<ld> prob(n);
  rep(i,0,k) {
    int x;
    ld p;
    cin>>x>>p;
    --x;
    prob[x] = p;
  }
  if(*max_element(all(prob)) < 1) {
    cout << "impossible" << endl;
    exit(0);
  }

  vi nodes(n);
  iota(all(nodes),0);
  sort(all(nodes),[&](int x, int y){return d0[x]+dn[x] < d0[y]+dn[y];});
  ld ans = 0, scale = 1;
  for(int x : nodes) {
    ans += scale * prob[x] * (d0[x]+dn[x]);
    scale *= (1-prob[x]);
  }
  cout << setprecision(14) << fixed;
  cout << ans << endl;
}
