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
vector<vii> adj;
ll n;
vector<bool> B;
vector<bool> visited;
ll r = 0;

bool dfs(ll i) {
	if (visited[i]) return false;
	visited[i] = true;
	bool b = B[i];
	for (ii e : adj[i]) {
		bool be = dfs(e.x);
		r += e.y * be;
		b ^= be;
	}
	//cout << i << ": " << b << ", " << r << endl;
	//cout << B[i] << endl;
	return b;
}

void run() {
	cin >> n;
	adj = vector<vii>(n);
	B = vector<bool>(n, false);
	visited = vector<bool>(n, false);
	
	for (ll i = 0; i < n-1; i++) {
		ll a, b, w;
		cin >> a >> b >> w;
		a--; b--;
		adj[a].eb(b, w);
		adj[b].eb(a, w);
	}
	ll m;
	cin >> m;
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--; b--;
		B[a] = !B[a];
		B[b] = !B[b];
	}
	dfs(0);
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
