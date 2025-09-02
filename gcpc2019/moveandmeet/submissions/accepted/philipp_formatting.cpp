#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll manhattan(pair<ll,ll> a, pair<ll,ll> b) {
	return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
	ll x[2], y[2], d[2];
	for(int i = 0; i < 2; i++) {
		cin >> x[i] >> y[i] >> d[i];
	}

	if(manhattan({x[0], y[0]}, {x[1], y[1]}) > d[0] + d[1]) {
		cout << endl << "  impossible\n" << endl;
		return 0;
	}

	if((abs(x[0]) + abs(y[0]) + d[0]) % 2 != (abs(x[1]) + abs(y[1]) + d[1]) % 2) {
		cout << endl << "     " << endl << "\timpossible\t";
		return 0;
	}

	int lil, big;
	if(d[0] < d[1]) {
		lil = 0;
	} else {
		lil = 1;
	}
	big = 1 - lil;
	ll res[2];
	ll diff = -1;
	if(y[big] - y[lil] > diff) {
		res[0] = x[lil];
		res[1] = y[lil] + d[lil];
		diff = y[big] - y[lil];
	}
	if(x[big] - x[lil] > diff) {
		res[0] = x[lil] + d[lil];
		res[1] = y[lil];
		diff = x[big] - x[lil];
	}
	if(y[lil] - y[big] > diff) {
		res[0] = x[lil];
		res[1] = y[lil] - d[lil];
		diff = y[lil] - y[big];
	}
	if(x[lil] - x[big] > diff) {
		res[0] = x[lil] - d[lil];
		res[1] = y[lil];
		diff = x[lil] - x[big];
	}
	cout << '\t' << res[0] << endl << "      " << res[1];
}
