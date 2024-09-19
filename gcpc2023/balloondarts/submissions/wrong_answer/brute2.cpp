#include <bits/stdc++.h>

using namespace std;

#define sz(a) (ll((a).size()))
#define all(a) (a).begin(),(a).end()

using ll = long long;
using vll = vector<ll>;

chrono::time_point<chrono::system_clock> start_time = chrono::system_clock::now();
bool kill() {
	using namespace chrono;
	const auto n = system_clock::now();
	return duration_cast<milliseconds>(n - start_time).count() > 900;
}

struct pt{
	ll x,y;
};

// 1=ccw, 0=straight, -1=cw
int ccw(const pt& p0, const pt& p1, const pt& p2) {
	ll d1 =(p1.x-p0.x)*(p2.y-p0.y);
	ll d2 =(p2.x-p0.x)*(p1.y-p0.y);
	return (d1-d2>0)-(d2-d1>0);
}

vector<pt> filter(const vector<pt>& p, pt a, pt b) {
	vector<pt> res;
	copy_if(all(p), back_inserter(res), [&](const pt& x) { return ccw(x, a, b) != 0; });
	return res;
}

bool solve(const vector<pt>& p, const vll& rest, ll k) {
	if (sz(rest) <= 2*k) return true;
	for (ll i = 0; i < min<ll>(sz(rest), 6) and not kill(); i++)
		for (ll j = 0; j < i; j++) {
			vll nr;
			copy_if(all(rest), back_inserter(nr), [&](const ll& x) { return ccw(p[x], p[rest[i]], p[rest[j]]) != 0; });
			if (solve(p, nr, k-1))
				return true;
		}
	return false;
}

bool solve(const vector<pt>& p) {
	vll rest(sz(p));
	iota(all(rest), 0);
	return solve(p, rest, 3);
}

int main() {
	ll n;
	cin >> n;
	vector<pt> p(n);
	for (pt& a : p) cin >> a.x >> a.y;
	cout << ("impossible" + 2*solve(p)) << endl;
	return 0;
}
