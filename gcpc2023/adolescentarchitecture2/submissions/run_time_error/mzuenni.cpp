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
						  {1.0l / sqrt(3.0),	1.0l,							cos(pi/12)},
						  {1.0l / sqrt(2.0l),	(2 + sqrt(3.0l)) / sqrt(3.0l),	1.0l}};

bool canContain(ll t, ll a, ll ot, ll oa) {
	return oa * mat[ot][t] < a;
}

constexpr ll lim = 100'006;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	//calculate all the grundy numbers...
	ll largest[3][3] = {{0, 0, 0},
	                    {0, 0, 0},
	                    {0, 0, 0}};

	vector<mex> todo(3);
	vector<vector<ll>> grundy(3, vector<ll>(2*lim, -1));
	map<ll, vector<pair<ll, ll>>> byGrundy;

	auto process = [&](ll t, ll a){
		for (ll ot : {0, 1, 2}) {
			while (canContain(t, a, ot, largest[t][ot] + 1)) {
				largest[t][ot]++;
				ll reachable = grundy[ot][largest[t][ot]];
				todo[t].seen.insert(reachable);
			}
		}
		grundy[t][a] = todo[t].getNext();
		byGrundy[grundy[t][a]].push_back({t, a});
	};

	for (ll c = 1, t = 1, s = 1; c < lim; c++) {
		while (canContain(0, c, 2, s) || canContain(0, c, 1, t)) {
			if (canContain(2, s, 1, t) || !canContain(0, c, 2, s)) {
				process(1, t);
				t++;
			} else {
				process(2, s);
				s++;
			}
		}
		process(0, c);
	}

	//solve the problem...
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
	for (auto [t, a] : in) combined ^= grundy[t][a];

	ll res = 0;
	for (auto [t, a] : in) {
		auto it = byGrundy.find(combined ^ grundy[t][a]);
		if (it == byGrundy.end()) continue;
		for (auto [ot, oa] : it->second) {
			if (canContain(t, a, ot, oa)) res++;
		}
	}
	cout << res << endl;
}
