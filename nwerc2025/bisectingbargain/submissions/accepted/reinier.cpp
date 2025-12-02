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

vi S(ll n) {
	vi R;
	if (n%2 == 1) {
		for (ll i = 0; i < n/2; i++) {
			R.pb(2);
		}
		R.pb(1);
	} else if (n%5 == 1 || n%5 == 2) {
		for (ll i = 0; i < n/5; i++) {
			R.pb(5);
		}
		R.pb(n%5);
	} else if (n%5 == 3) {
		for (ll i = 0; i < n/5; i++) {
			R.pb(5);
		}
		R.pb(1);
		R.pb(2);
	} else if (n%4 == 2) {
		for (ll i = 0; i < n/2; i++) {
			R.pb(2);
		}
	}
	return R;
}

// START OF ACTUAL PROGRAM, START READING HERE

void run() {
	ll n;
	cin >> n;
	vi R;
	bool res = true;
	for (ll p = 100; p >= 1; p /= 10) {
		vi Ri = S(n/p);
		if (Ri.size() == 0) {
			for (ll i = 0; i < n/p; i++) {
				R.pb(p);
			}
		} else {
			res = false;
			for (ll r : Ri) {
				R.pb(r*p);
			}
		}
		n %= p;
	}
	if (res) {
		cout << "splittable" << endl;
	} else {
		cout << R.size() << endl;
		for (ll r : R) {
			cout << r << " ";
		}
		cout << endl;
	}
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
