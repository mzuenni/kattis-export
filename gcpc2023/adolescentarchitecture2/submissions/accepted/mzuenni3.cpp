#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using lll = __int128;
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
	ll a;
	if (t == 0) a = expected * mat[1][0];
	if (t == 1) a = expected + 1;
	if (t == 2) a = expected * mat[1][2];
	while (grundy(t, a) < expected) a++;
	if (a <= 0 || grundy(t, a) != expected) return -1;
	else return a;
}

lll sq(lll x) {
	return x*x;
}

bool canContain(ll t, ll a, ll ot, ll oa) {
	if (ot == t) return oa < a;
	if (ot == 0 && t == 1) return sq(oa) * 12 < sq(a);
	if (ot == 0 && t == 2) return oa * 2 < a;
	if (ot == 1 && t == 0) return sq(oa) < sq(a) * 3;
	if (ot == 1 && t == 2) return sq(oa) <= sq(a) * 2 && sq(sq(oa)) * 3 < 4 * sq((sq(a) * 2 - sq(oa)));
	if (ot == 2 && t == 0) return sq(oa) < sq(a) * 2;
	if (ot == 2 && t == 1) return oa <= a && sq(oa) * 4 < 3 * sq(a-oa); //is this wrong without oa <= a?
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
