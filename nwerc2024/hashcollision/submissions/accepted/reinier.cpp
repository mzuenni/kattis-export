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

vi A;

ll query(ll i, ll j) {
	cout << "? " << i << " " << j+1 << endl;
	ll r;
	cin >> r;
	return r-1;
}

bool queryplusplus(ll i, ll j) {
	ll r = query(i, j);
	if (A[r] >= 0) {
		ll P = abs(i - A[r]);
		ll a = query(((-j-1-1)%P+P)%P+1, j);
		cout << "! " << j+1 << " " << a+1 << endl;
		return true;
	}
	A[r] = i;
	return false;
}

void run() {
	ll n;
	cin >> n;
	ll s = (ll) (sqrt((ld) n) + 1);
	ll a = query(n, 0);
	A = vi(n, -1);
	A[a] = 0;
	for (ll i = 1; i < s; i++) {
		if (queryplusplus(i, a)) return;
	}
	for (ll i = s; i <= n; i += s) {
		if (queryplusplus(i, a)) return;
	}
	queryplusplus(n, a);
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
