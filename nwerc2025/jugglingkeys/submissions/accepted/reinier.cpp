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

void run() {
	ll n, k, q;
	cin >> n >> k >> q;
	vector<pair<ii, ll>> E;
	vector<bool> R(q);
	for (ll i = 0; i < q; i++) {
		ll p, l, r;
		cin >> p >> l >> r;
		E.pb({{l,-1},i});
		E.pb({{r,1},i});
	}
	sort(all(E));
	ll a = n;
	for (pair<ii, ll> e : E) {
		if (a == 0) {
			R[e.y] = true;
		}
		a += e.x.y;
	}
	ll b = k;
	for (pair<ii, ll> e : E) {
		b += R[e.y]*e.x.y;
		if (b < 0) {
			cout << "impossible" << endl;
			return;
		}
	}
	for (bool r : R) {
		cout << r;
	}
	cout << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
