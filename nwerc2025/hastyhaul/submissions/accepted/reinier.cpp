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
vvi binom(65, vi(65, 0));

ll get_index(vector<bool>& A, ll s, ll e, ll n, ll k) {
	if (k == 0) return 0;
	ll res = 0;
	if ((n+k)%2 == 0) {
		ll i = s;
		while (!A[i]) {
			res += binom[e-i-1][k-1];
			i++;
		}
		return res + get_index(A, i+1, e, e-i-1, k-1);
	} else {
		ll i = e-1;
		while (!A[i]) {
			res += binom[i-s][k-1];
			i--;
		}
		return res + get_index(A, s, i, i-s, k-1);
	}
}

void get_arr(vector<bool>& B, ll s, ll e, ll n, ll k, ll index) {
	if (k == 0) {
		for (ll i = s; i < e; i++) B[i] = false;
		return;
	}
	if ((n+k)%2 == 0) {
		ll i = s;
		while (index >= binom[e-i-1][k-1]) {
			B[i] = false;
			index -= binom[e-i-1][k-1];
			i++;
		}
		B[i] = true;
		get_arr(B, i+1, e, e-i-1, k-1, index);
	} else {
		ll i = e-1;
		while (index >= binom[i-s][k-1]) {
			B[i] = false;
			index -= binom[i-s][k-1];
			i--;
		}
		B[i] = true;
		get_arr(B, s, i, i-s, k-1, index);
	}
}

void run() {
	ll h, w, k;
	cin >> h >> w >> k;
	ll n = h*w;
	vector<bool> A(n);
	for (ll r = 0; r < h; r++) {
		string s;
		cin >> s;
		for (ll c = 0; c < w; c++) {
			A[r*w+c] = (s[c] == '#');
		}
	}
	if (binom[n][k]%2 != 0) {
		cout << "risky" << endl;
		return;
	}
	ll index = get_index(A, 0, n, n, k);
	vector<bool> B(n);
	get_arr(B, 0, n, n, k, index + 1 - 2*(index%2));
	
	ll i1 = -1, i2 = -1;
	for (ll i = 0; i < n; i++) {
		if (A[i] && !B[i]) {
			i1 = i;
		} else if (!A[i] && B[i]) {
			i2 = i;
		}
	}
	cout << i1/w+1 << " " << i1%w+1 << "\n" << i2/w+1 << " " << i2%w+1 << "\n";
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);

	for (ll i = 0; i <= 64; i++) {
		for (ll j = 0; j <= 64; j++) {
			if (j > i) {
				binom[i][j] = 0;
			} else if (i == j) {
				binom[i][j] = 1;
			} else if (j == 0) {
				binom[i][j] = 1;
			} else {
				binom[i][j] = binom[i-1][j] + binom[i-1][j-1];
			}
		}
	}
	
	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		run();
	}
    return 0;
}
