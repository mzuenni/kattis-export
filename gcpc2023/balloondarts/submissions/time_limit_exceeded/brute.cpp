#include <bits/stdc++.h>

using namespace std;

#define sz(a) (ll((a).size()))
#define all(a) (a).begin(),(a).end()

using ll = long long;
using vll = vector<ll>;

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

bool solve(const vector<pt>& p, const vector<bool>& remaining, ll k) {
	vll rest;
	for (ll i = 0; i < sz(p); i++) if (remaining[i]) rest.emplace_back(i);
	if (sz(rest) <= 2*k) return true;
	for (ll i = 0; i < sz(rest); i++)
		for (ll j = 0; j < i; j++) {
			auto nr = remaining;
			for (ll x : rest)
				if (ccw(p[rest[i]], p[rest[j]], p[x]) == 0)
					nr[x] = false;
			if (solve(p, nr, k-1))
				return true;
		}
	return false;
}

bool solve(const vector<pt>& p) {
	std::vector<bool> remaining(p.size(), true);
	return solve(p, remaining, 3);
}

int main() {
	ll n;
	cin >> n;
	vector<pt> p(n);
	for (pt& a : p) cin >> a.x >> a.y;
	cout << ("impossible" + 2*solve(p)) << endl;
	return 0;
}
