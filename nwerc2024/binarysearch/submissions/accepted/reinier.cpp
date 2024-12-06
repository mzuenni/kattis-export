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

vvi adj;
vi R;

ll dfs(ll i) {
	if (R[i] != 0) return R[i];
	R[i] = -1;
	ll r = 1;
	for (ll j : adj[i]) {
		ll s = dfs(j);
		if (s < 0) return R[i] = -1;
		r = max(r, s+1);
	}
	return R[i] = r;
}

void run() {
	ll n, m;
	cin >> n >> m;
	adj = vvi(2*n);
	R = vi(2*n, 0);
	vi A(n);
	for (ll i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (ll i = 0; i < m; i++) {
		ll u, v;
		cin >> u >> v;
		u--; v--;
		if (A[u] == A[v]) {
			adj[u].pb(v+n);
			adj[v].pb(u+n);
		} else {
			adj[u+n].pb(v);
			adj[v+n].pb(u);
		}
	}
	vvi S(2, vi(2,0));
	for (ll i = 0; i < 2*n; i++) {
		ll r = dfs(i);
		if (r < 0) {
			cout << "infinity" << endl;
			return;
		}
		S[i/n][A[i%n]] = max(S[i/n][A[i%n]], r);
	}
	cout << min(min(S[0][0], S[0][1]), min(S[1][0], S[1][1]))+1 << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
