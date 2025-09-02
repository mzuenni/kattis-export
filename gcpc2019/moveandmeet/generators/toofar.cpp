// the ranges don't intersect

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using vl = vector<ll>;
using vvl = vector<vl>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using vb = vector<bool>;
using vs = vector<string>;
const ll oo = 0x3f3f3f3f3f3f3f3fLL;
const ld eps = 1e-9;
#define sz(c) ll((c).size())
#define all(c) begin(c),end(c)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define xx first
#define yy second
#define FOR(i,a,b) for(ll i = (a); i < (b); i++)
#define FORD(i,a,b) for(ll i = ll(b)-1; i >= (a); i--)
#define TR(X) ({ if(1) cerr << "TR: " << (#X) << " = " << (X) << endl; })

const ll lowest = -1'000'000'000;
const ll highest = 1'000'000'000;

int main() {
	cin.sync_with_stdio(0);

	int seed;
	cerr << "seed pls" << endl;
	cin >> seed;
	srand(seed);

	ll x[2], y[2], d[2];
	FOR(i,0,2) {
		x[i] = oo;
		while(x[i] < lowest || x[i] > highest) {
			x[i] = rand() - 1'000'000'000;
		}
		y[i] = oo;
		while(y[i] < lowest || y[i] > highest) {
			y[i] = rand() - 1'000'000'000;
		}
		d[i] = oo;
		while(d[i] > highest) {
			d[i] = rand();
		}
	}

	if(abs(x[0] - x[1]) + abs(y[0] - y[1]) <= d[0] + d[1]) {
		cerr << "do it again lol" << endl;
	} else {
		if((x[0]+y[0]+d[0]) % 2 != (x[1]+y[1]+d[1]) % 2) {
			cerr << "FYI: this wouldn't work regardless of dist" << endl;
		}
		FOR(i,0,2) {
			cout << x[i] << ' ' << y[i] << ' ' << d[i] << endl;
		}
	}
}
