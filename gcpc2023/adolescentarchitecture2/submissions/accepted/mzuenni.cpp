#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

struct mex {
	set<ll> seen;
	ll next;

	ll getNext() {
		while (seen.find(next) != seen.end()) next++;
		return next;
	}
};

constexpr ld pi = acos(-1.0l);
constexpr ld mat[3][3] = {{1.0l,				sqrt(12.0l),					2.0l},
						  {1.0l / sqrt(3.0l),	1.0l,							cos(pi/12)},
						  {1.0l / sqrt(2.0l),	(2 + sqrt(3.0l)) / sqrt(3.0l),	1.0l}};

ll grundy(ll t, ll a) {
	if (t == 0) return max<ll>(a / mat[1][0], a + 1);
	if (t == 1) return a - 1;
	if (t == 2) return a / mat[1][2];
	return -1;
}

ll byGrundy(ll t, ll expected) {
	ll l = 1;
	ll r = 3'000'000'000;
	while (l + 1 < r) {
		ll m = (l + r) / 2;
		if (grundy(t, m) <= expected) l = m;
		else r = m;
	}
	if (grundy(t, l) != expected) return -1;
	else return l;
}

bool canContain(ll t, ll a, ll ot, ll oa) {
	return oa * mat[ot][t] < a;
}

constexpr ll lim = 500'006;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	vector<pair<ll, ll>> in(n);
	string ts;
	for (auto& [t, a] : in) {
		cin >> ts >> a;
		if (ts == "circle") t = 0;
		if (ts == "triangle") t = 1;
		if (ts == "square") t = 2;
	}

	ll combined = 0;
	for (auto [t, a] : in) combined ^= grundy(t, a);

	ll res = 0;
	for (auto [t, a] : in) {
		ll needed = combined ^ grundy(t, a);
		for (ll ot : {0, 1, 2}) {
			ll oa = byGrundy(ot, needed);
			if (oa < 0 || !canContain(t, a, ot, oa)) continue;
			res++;
		}
	}
	cout << res << endl;
}
