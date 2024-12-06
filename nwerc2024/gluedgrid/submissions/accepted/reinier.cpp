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
	ll h, w;
	cin >> h >> w;
	vector<vector<bool>> G(h+2, vector(w+2, true));
	vector<vector<bool>> G2(h+3, vector(w+3, false));
	for (ll i = 0; i < h; i++) {
		string s;
		cin >> s;
		for (ll j = 0; j < w; j++) {
			if (s[j] == '.') {
				G[i+1][j+1] = false;
			}
		}
	}
	for (ll i = 0 ; i < h+2; i++) {
		for (ll j = 0; j < w+2; j++) {
			if (G[i][j]) {
				G2[i][j] = true;
				G2[i+1][j] = true;
				G2[i][j+1] = true;
				G2[i+1][j+1] = true;
			}
		}
	}

	ll cc = 0;
	vvi C(h+2, vi(w+2, 0));
	vvi C2(h+3, vi(w+3, 0));
	vi Cl(h*w, 0);
	deque<pair<ii, pair<bool, bool>>> Q;
	Q.push_back({{h, w},{true, false}});
	while (!Q.empty()) {
		pair<ii, pair<bool, bool>> p = Q.front(); Q.pop_front();
		ll i = p.x.x, j = p.x.y; bool b = p.y.x, b2 = p.y.y;
		if (!b2) {
			if (G[i][j] || C[i][j] > 0) continue;
			if (b) cc++;
			C[i][j] = cc;
			Cl[(i-1)*w+(j-1)] = cc;
			for (ii a : vii{{i,j},{i+1,j},{i,j+1},{i+1,j+1}}) {
				Q.push_back({a, {true, true}});
			}
			for (ii a : vii{{i-1,j}, {i,j-1}, {i+1,j}, {i,j+1}}) {
				Q.push_back({a, {true, false}});
			}
		} else {
			if (G2[i][j] || C2[i][j] > 0) continue;
			if (b) cc++;
			C2[i][j] = cc;
			for (ii a : vii{{i-1,j-1},{i,j-1},{i-1,j},{i,j}}) {
				Q.push_front({a, {false, false}});
			}
			for (ii a : vii{{i-1,j}, {i,j-1}, {i+1,j}, {i,j+1}}) {
				Q.push_front({a, {false, true}});
			}
		}
	}

	vi A(h*w, 0);
	for (ll i = 0; i < h*w; i++) {
		cin >> A[i];
		A[i]--;
	}
	A[h*w-1] = h*w-1;

	//for (ll i = 0; i < h*w; i++) {
	//	cout << Cl[i] << " " << endl;
	//}
	//cout << endl;

	vector<bool> P(cc+1, false);
	for (ll i = 0; i < h*w; i++) {
		while (A[i] != i) {
			if (Cl[A[i]] != Cl[A[A[i]]]) {
				cout << "impossible" << endl;
				return;
			} else {
				P[Cl[A[i]]] = !P[Cl[A[i]]];
				swap(A[i], A[A[i]]);
			}
		}
	}
	
	bool res = true;
	for (ll i = 0; i < cc+1; i++) {
		if (P[i]) res = false;
	}
	if (res) {
		cout << "possible" << endl;
	} else {
		cout << "impossible" << endl;
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
