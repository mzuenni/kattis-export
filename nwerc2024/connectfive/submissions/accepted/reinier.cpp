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

ll get_res(vi X, vi Y) {
	ll n = X.size();
	vi Xs = X;
	vi Ys = Y;
	sort(all(Xs));
	sort(all(Ys));
	ll r = Xs[1]-Xs[0] + Xs[n-1]-Xs[n-2] + Ys[1]-Ys[0] + Ys[n-1]-Ys[n-2];
	for (ll i = 0; i < n; i++) {
		if (X[i] == Xs[0]) X[i] = Xs[1];
		if (Y[i] == Ys[0]) Y[i] = Ys[1];
		if (X[i] == Xs[n-1]) X[i] = Xs[n-2];
		if (Y[i] == Ys[n-1]) Y[i] = Ys[n-2];
	}


	ll w = Xs[n-2]-Xs[1], h = Ys[n-2]-Ys[1];
	if (w == 0) {
		return r + h;
	}
	if (h == 0) {
		return r + w;
	}


	for (ll i = 0; i < n; i++) {
		for (ll j = i+1; j < n; j++) {
			if (X[i] == X[j] && Y[i] == Y[j]) {
				X.erase(X.begin()+j); Y.erase(Y.begin()+j);
				return r + get_res(X, Y);
			}
		}
	}

	for (ll i = 0; i < n; i++) {
		if (X[i] != Xs[1] && X[i] != Xs[n-2] && Y[i] != Ys[1] && Y[i] != Ys[n-2]) {
			return r + 2*w + 2*h + min(w, h);
		}
	}

	return r + 2*w + 2*h;
}

void run() {
	vi X(5), Y(5);
	for (ll i = 0; i < 5; i++) {
		cin >> X[i] >> Y[i];
	}
	cout << get_res(X, Y) << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
