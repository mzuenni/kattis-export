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

void move(ll a, ll b, vi& A, vi& B, vii& R) {
	//cout << a << b << endl;
	//for (ll i = 0; i < A.size(); i++) {
	//	cout << A[i] << " ";
	//}
	//cout << endl;
	//cout << endl;
	ll n = A.size();
	if (a == b) return;
	R.eb(a+1, b+1);
	ll x = A[a], y = A[a+1], z = A[a+2]; 
	for (ll j = 0; j < n; j++) {
		if (B[j] >= a+3) {
			B[j] -= 3;
		}
		if (B[j] >= b) {
			B[j] += 3;
		}
	}
	B[x] = b; B[y] = b+1; B[z] = b+2;
	for (ll i = 0; i < n; i++) {
		A[B[i]] = i;
	}
	return;
}

void swap(vi& A, vi& B, vii& R) {
	ll n = A.size();
	move(n-4, n-3, A, B, R);
	move(n-5, n-3, A, B, R);
	move(n-5, n-3, A, B, R);
}

void cycle(vi& A, vi& B, vii& R) {
	ll n = A.size();
	move(n-4, n-3, A, B, R);
}

void run() {
	ll n;
	cin >> n;
	vi A(n);
	vi B(n);
	for (ll i = 0; i < n; i++) {
		cin >> A[i];
		A[i]--;
		B[A[i]] = i;
	}
	vii R;
	for (ll i = 0; i < n-5; i++) {
		if (B[i] >= n-2) {
			move(n-3, n-5, A, B, R);
		}
		move(B[i], i, A, B, R);
	}
	for (ll i = n-4; i <= n-1; i++) {
		if (A[n-5] != i) {
			while (A[n-1] != i) cycle(A, B, R);
			swap(A, B, R);
		}
		while (A[n-2] != i-1) cycle(A, B, R);
		swap(A, B, R);
	}

	cout << R.size() << endl;
	for (ii r : R) {
		cout << r.x << " " << r.y << endl;
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
