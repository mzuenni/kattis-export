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

bool run(ll n, vector<pair<ii,ii>> A) {
	for (ll i = 0; i < n; i++) {
		if (A[i].x > A[i].y) swap(A[i].x, A[i].y);
	}

	vector<pair<ll, pair<ii, ii>>> lengths;
	for (ll i = 0; i < n; i++) {
		lengths.pb({abs(A[i].x.x-A[i].y.x) + abs(A[i].x.y-A[i].y.y), A[i]});
	}
	sort(all(lengths));
	ll max_len = lengths[n-4].x;

	vi V0, H0;
	for (ll i = n-3; i < n; i++) {
		if (lengths[i].y.x.x == lengths[i].y.y.x) V0.pb(i);
		else H0.pb(i);
	}
	if (V0.size() == 1) {
		pair<ii,ii> h1 = lengths[H0[0]].y;
		pair<ii,ii> h2 = lengths[H0[1]].y;
		if (h1.x.y > h2.x.y) swap(h1, h2);
		pair<ii,ii> v = lengths[V0[0]].y;
		//cout << h1.x.x << " " << h1.x.y << ", " << h1.y.x << " " << h1.y.y << endl;
		//cout << h2.x.x << " " << h2.x.y << ", " << h2.y.x << " " << h2.y.y << endl;
		//cout << v.x.x << " " << v.x.y << ", " << v.y.x << " " << v.y.y << endl;
		ll s = h2.x.y - h1.x.y;
		if (h1.x.x <= v.x.x && h2.x.x <= v.x.x
				&& h1.y.x >= v.x.x+s && h2.y.x >= v.x.x+s
				&& v.x.y <= h1.x.y && v.y.y >= h2.x.y
				&& s > max_len && n >= 5) {
			ll v2i = -1, v3i = -1;
			for (ll i = 0; i < n-3; i++) {
				if (lengths[i].y.x.x == lengths[i].y.y.x
						&& lengths[i].y.x.x == v.x.x+s) {
					if (lengths[i].y.x.y <= h1.x.y && lengths[i].y.y.y >= h1.x.y) {
						v2i = i;
					}
					if (lengths[i].y.x.y <= h2.x.y && lengths[i].y.y.y >= h2.x.y) {
						v3i = i;
					}
				}
			}
			for (ll i = 0; i < n-3; i++) {
				if (v2i != -1 && i != v2i && lengths[v2i].y.y.y + lengths[i].x >= h2.x.y) {
					return true;
				}
				if (v3i != -1 && i != v3i && lengths[v3i].y.x.y - lengths[i].x <= h1.x.y) {
					return true;
				}
				if (v2i != -1 && v3i != -1 && i != v2i && i != v3i
						&& lengths[v2i].y.y.y + lengths[i].x >= lengths[v3i].y.x.y) {
					return true;
				}
			}
		}
	}

	sort(all(A));
	vector<pair<ii,ii>> V, H;
	for (pair<ii, ii> p : A) {
		if (p.x.x == p.y.x) V.pb(p);
		else H.pb(p);
	}
	vector<pair<ll, pair<ll, ll>>> Q;
	for (ll i = 0; i < H.size(); i++) {
		pair<ii, ii> p = H[i];
		Q.pb({p.x.x, {-1, i}});
		Q.pb({p.y.x, {0, i}});
	}
	for (ll i = 0; i < V.size(); i++) {
		pair<ii, ii> p = V[i];
		Q.pb({p.x.x, {1, i}});
	}
	sort(all(Q));

	set<ii> L;
	ll intersections = 0;
	for (pair<ll, pair<ll, ll>> e : Q) {
		if (e.y.x == -1) {
			L.insert({H[e.y.y].y.y, H[e.y.y].y.x});
		} else if (e.y.x == 0) {
			L.erase({H[e.y.y].y.y, H[e.y.y].y.x});
		} else {
			ii start = {V[e.y.y].x.y, -1'000'000'000'000LL}, end = {V[e.y.y].y.y, 1'000'000'000'000LL};
			auto it = L.lower_bound(start);
			vii B;
			while (it != L.end() && *it <= end) {
				B.pb({-(*it).y + e.x, (*it).x});
				intersections++;
				if (intersections > 4*n) return true;
				it++;
			}
			sort(all(B));
			set<ii> C;
			for (ii b : B) {
				auto it2 = C.lower_bound({b.y, -b.x});
				ii c2 = {-b.x, b.y};
				if (it2 != C.end()) {
					ii c3 = {(*it2).y, (*it2).x};
					if (abs(c2.y - c3.y) <= min(c2.x, max_len)) return true;
				}
				if (it2 != C.begin()) {
					it2--;
					ii c1 = {(*it2).y, (*it2).x};
					if (abs(c2.y - c1.y) <= min(c2.x, max_len)) return true;
				}
				C.insert({b.y, -b.x});
			}
		}
	}

	return false;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		ll n;
		cin >> n;
		vector<pair<ii, ii>> A(n);
		for (ll j = 0; j < n; j++) {
			cin >> A[j].x.x >> A[j].x.y >> A[j].y.x >> A[j].y.y;
		}
		bool res = false;
		for (ll j = 0; j < 4; j++) {
			if (run(n, A)) {
				res = true;
				cout << "yes\n";
				break;
			}
			vector<pair<ii,ii>> B(n);
			for (ll k = 0; k < n; k++) {
				B[k] = {{-A[k].x.y, A[k].x.x}, {-A[k].y.y, A[k].y.x}};
			}
			A = B;
		}
		if (!res) cout << "no\n";
	}
    return 0;
}
