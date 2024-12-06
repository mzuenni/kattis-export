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

typedef __int128 ll;
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
	int n;
	cin >> n;
	vi X(n), Y(n);
	ll sx = 0, sy = 0, ssx = 0, ssy = 0;
	for (ll i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		X[i] = x;
		Y[i] = y;
		sx += (i-1)*X[i];
		sy += (i-1)*Y[i];
		ssx += X[i];
		ssy += Y[i];
	}

	ll r = 0;
	ll a = 0;
	for (ll i = 0; i < n; i++) {
		r += X[i]*sy - Y[i]*sx;
		sx += n*X[i] - ssx;
		sy += n*Y[i] - ssy;
		a += X[i]*Y[(i+1)%n] - Y[i]*X[(i+1)%n];
	}

	cout << -((ld)r)/a << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
