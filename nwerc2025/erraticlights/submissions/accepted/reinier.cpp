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
	ll n;
	cin >> n;
	ll a = 0, b = 0, c = 0;
	string s;
	cin >> s;
	for (ll i = 0; i < n; i++) {
		if (s[i] == 'r') a++;
		else if (s[i] == 'g') b++;
		else c++;
	}
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);

	vector<vector<ld>> A(n+1, vector<ld>(n+1, 0));
	for (ll s = 0; s <= n; s++) {
		for (ll i = 0; i <= s; i++) {
			if (i > n || s-i > n) continue;
			if (2*i > s) {
				A[i][s-i] = A[s-i][i];
			} else if (s-i > n-s) {
				A[i][s-i] = A[i][n-s];
			} else if (i == 0) {
				A[i][s-i] = (s-i)*3;
			} else {
				A[i][s-i] = 1.5 + 0.5*A[i-1][s-i] + 0.5*A[i-1][s-i+1];
			}
		}
	}
	//for (ll i = 0; i <= n; i++) {
	//	for (ll j = 0; j <= n; j++) {
	//		cout << A[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << A[a][b] << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
