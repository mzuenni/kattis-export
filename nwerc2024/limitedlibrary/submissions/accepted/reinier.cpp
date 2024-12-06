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
	ll n, m, x, y;
	cin >> n >> m >> x >> y;
	vi A(n);
	vi B(m);
	for (ll i = 0; i < n; i++) {
		cin >> A[i];
	}
	for (ll i = 0; i < m; i++) {
		cin >> B[i];
	}
	sort(all(A));
	sort(all(B));

	vi C(n+1, 0);
	ll r = 0;
	for (ll i = 0, j = 0; i <= n; i++) {
		if (i != 0) while (j < m && B[j] <= A[i-1]) j++;
		if (m-j > (n-i)*x) {
			cout << "impossible" << endl;
			return;
		}
		if (i != 0) C[i] = min(C[i-1] + y, j);
		if (m-C[i] <= (n-i)*x) r = i;
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
