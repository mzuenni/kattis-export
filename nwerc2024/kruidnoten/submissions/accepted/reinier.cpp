#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <charconv>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl

const ld PI = acos(-1.0);
template<class T> using min_queue =
priority_queue<T, vector<T>, greater<T>>;
template<class T> int sz(const T &x) {
    return (int) x.size(); // copy the ampersand(&)!
}

// START OF ACTUAL PROGRAM, START READING HERE

vi dijkstra(const vector<vii> &G, int s) {
	vi d(sz(G), LLONG_MAX);
	set<ii> Q{ii{d[s] = 0, s}};
	while (!Q.empty()) {
		int v = Q.begin()->y;
		Q.erase(Q.begin());
		for (ii e : G[v]) if (d[v] + e.y < d[e.x]) {
			Q.erase(ii(d[e.x], e.x));
			Q.emplace(d[e.x] = d[v] + e.y, e.x);
		}
	}
	return d;
}


void run() {
	ll n, m, k;
	cin >> n >> m >> k;
	vector<vii> adj(n);
	vector<ld> P(n, 0);
	bool pos = false;
	for (ll i = 0; i < m; i++) {
		ll u, v, l;
		cin >> u >> v >> l;
		u--; v--;
		adj[u].eb(v, l);
		adj[v].eb(u, l);
	}
	for (ll i = 0; i < k; i++) {
		ll j;
		ld p;
		cin >> j >> p;
		j--;
		P[j] = p;
		if (p == 1) pos = true;
	}
	if (!pos) {
		cout << "impossible" << endl;
		return;
	}
	vi d0 = dijkstra(adj, 0);
	vi d1 = dijkstra(adj, n-1);
	vector<pair<ll, ld>> D(n);
	for (ll i = 0; i < n; i++) {
		D[i] = {d0[i] + d1[i], P[i]};
	}
	sort(all(D));
	ld rp = 1;
	ld r = 0;
	for (pair<ll, ld> p : D) {
		r += rp*p.x*p.y;
		rp *= 1-p.y;
	}
	cout << r << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
