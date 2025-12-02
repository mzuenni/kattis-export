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

ll lis(vi arr) {
	vi seq, back(sz(arr)), ans;
	REP(i, sz(arr)) {
		int res = 0, lo = 1, hi = sz(seq);
		while (lo <= hi) {
			int mid = (lo+hi)/2;
			if (arr[seq[mid-1]] <= arr[i]) res = mid, lo = mid+1;
			else hi = mid-1;
		}
		if (res < sz(seq)) seq[res] = i;
		else seq.pb(i);
		back[i] = res == 0 ? -1 : seq[res-1];
	}
	int at = seq.back();
	while (at != -1) ans.pb(at), at = back[at];
	reverse(all(ans));
	return sz(ans);
}

void run() {
	ll n;
	cin >> n;
	vii A;
	for (ll j = 0; j < n; j++) {
		ll i;
		cin >> i;
		ii p1 = {2*j+1, 2*i-2*j-2};
		ii p2 = {2*i+2*j-2*n, 2*n-2*j-1};
		if (p1.x >= 0 && p1.y >= 0) {
			A.pb(p1);
		}
		if (p2.x >= 0 && p2.y >= 0) {
			A.pb(p2);
		}
	}
	sort(all(A));
	//for (ii a : A) {
	//	cout << a.x << " " << a.y << endl;
	//}
	vi B;
	for (ii a : A) {
		B.pb(a.y);
	}
	cout << n-lis(B) << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
