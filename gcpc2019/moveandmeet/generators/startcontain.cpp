//one range contains the other starting point but not the whole range, while the other range does not contain the non-self starting point.

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

const ll lowest = -1'000'000'000'000;
const ll highest = 1'000'000'000'000;

ll myrand() {
	return (ll(rand()) << 31ll) + ll(rand());
}

int main() {
	cin.sync_with_stdio(0);

	int seed;
	cerr << "seed pls" << endl;
	cin >> seed;
	srand(seed);

	ll x[2], y[2], d[2];
	while(true) {
		FOR(i,0,2) {
			x[i] = myrand() % (highest - lowest) + lowest;
			y[i] = myrand() % (highest - lowest) + lowest;
		}
		ll dist = abs(x[1] - x[0]) + abs(y[1] - y[0]);
		d[0] = myrand() % dist;
		d[1] = -1;
		ll cnt = 0;
		while(d[1] < dist) {
			if(cnt == 10'000) {
				break;
			}
			d[1] = myrand() % min(highest, (dist+d[0]));
			cnt++;
		}
		if(cnt == 10'000) {
			continue;
		}
		break;
	}
	if(myrand() % 2) {
		swap(d[0], d[1]);
	}

	if(abs(x[0]+y[0]+d[0]) % 2 != abs(x[1]+y[1]+d[1]) % 2) {
		cerr << "mod2 impossible case" << endl;
	}
	FOR(i,0,2) {
		cout << x[i] << ' ' << y[i] << ' ' << d[i] << endl;
	}
}
