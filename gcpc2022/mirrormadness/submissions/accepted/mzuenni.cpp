#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using pt = complex<ll>;

struct ptComp {
	bool operator()(const pt& a, const pt& b) const {
		if (a.real() != b.real()) return a.real() < b.real();
		else a.imag() < b.imag();
	}
};

// Kreuzprodukt, 0, falls kollinear.
ll cross(pt a, pt b) {return imag(conj(a) * b);}
ll cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

pt readPT() {
	ll x, y;
	cin >> x >> y;
	return pt(x, y);
}

ll xy(const pt& p) {
	return p.real() + p.imag();
}

ll yx(const pt& p) {
	return p.real() - p.imag();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m; // number of corners of the polygon and number of points to print
	cin >> n >> m;

	vector<pt> in(n);
	for (ll i = 0; i < n; i++) in[i] = readPT();//must be in ccw order!
	in.push_back(in[0]);
	in.push_back(in[1]);

	pt s = readPT(); // start point must be on polygon and not a corner | could always be (0,0)
	pt d(1, 1);

	vector<pt> pos;
	vector<map<ll, vector<pair<pt, ll>>>> sweep(2);
	ll last = -1;
	for (ll i = 0; i < n; i++) {
		pt from = in[i];
		pt to = in[i + 1];
		pt dir = to - from;
		dir /= abs(dir); // abs will be an integer
		do {
			from += dir;// skip first and include last point of segment
			ll id = sz(pos);
			pos.push_back(from);
			if (from == s) last = id;
			// dont include point if its an inner corner
			if (from != to) {// must be a corner (no 3 consecutive points should be colinear)
				sweep[0][xy(from)].push_back({from, id});
				sweep[1][yx(from)].push_back({from, id});
			} else {
				if (xy(in[i]) < xy(in[i+1]) && xy(in[i+1]) < xy(in[i+2]) ||
					xy(in[i]) > xy(in[i+1]) && xy(in[i+1]) > xy(in[i+2])) {
					sweep[0][xy(from)].push_back({from, id});
				}
				if (yx(in[i]) < yx(in[i+1]) && yx(in[i+1]) < yx(in[i+2]) ||
					yx(in[i]) > yx(in[i+1]) && yx(in[i+1]) > yx(in[i+2])) {
					sweep[1][yx(from)].push_back({from, id});
				}
			}
		} while(from != to);
	}

	vector<vector<ll>> adj(sz(pos));// technically this should form cycles i.e. all vertices should have degree 2
	for (ll i = 0; i < 2; i++) {
		for (auto& [_, cur] : sweep[i]) {
			sort(all(cur), [](const pair<pt, ll>& a, const pair<pt, ll>& b){
				return a.first.real() < b.first.real();// we can sort by almost anything
			});
			for (ll j = 0; j + 1 < sz(cur); j+=2) {
//cout << cur[j].first << " " << cur[j+1].first << endl;
				adj[cur[j].second].push_back(cur[j+1].second);
				adj[cur[j+1].second].push_back(cur[j].second);
			}
		}
	}
	assert(last >= 0);

	ll cur = -1;
	for (ll x : adj[last]) {
		pt dir = pos[x] - s;
		dir /= abs(dir.real());
		if (dir == d) cur = x;
	}
	assert(cur >= 0);

	cout << pos[cur].real() << " " << pos[cur].imag() << endl;
	for (ll i = 1; i < m; i++) {
		ll next = -1;
		for (ll x : adj[cur]) if (x != last) next = x;//sz(adj[cur]) == 2
		assert(next >= 0);
		last = cur;
		cur = next;
		cout << pos[cur].real() << " " << pos[cur].imag() << endl;
	}
}
