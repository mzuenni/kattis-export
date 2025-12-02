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
	map<string, ll> M;
	vector<string> N;
	vvi V;
	ll i = 0;
	for (ll j = 0; j < n; j++) {
		for (ll k = 0; k < 10; k++) {
			string s;
			cin >> s;
			if (M.find(s) == M.end()) {
				M[s] = i;
				V.pb(vi(12));
				V[i][11] = i;
				N.pb(s);
				i++;
			}
			ll mi = M[s];
			V[mi][k+1]--;
			V[mi][0]--;
		}
	}
	sort(all(V));
	bool tie = true;
	if (i == 1) {
		cout << N[0] << endl;
		return;
	}
	for (ll j = 0; j <= 10; j++) {
		if (V[0][j] != V[1][j]) tie = false;
	}
	if (tie) {
		cout << "tie" << endl;
	} else {
		cout << N[V[0][11]] << endl;
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
