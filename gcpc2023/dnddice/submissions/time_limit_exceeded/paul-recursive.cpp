#include <bits/stdc++.h>
using namespace std;

double prob(int t, int c, int o, int d, int i, int s) {
	if (s < t + c + o + d + i) return 0;
	if (s > 4*t + 6*c + 8*o + 12*d + 20*i) return 0;
	double res = 0;
	if (t > 0) {
		for (int x = 1; x <= 4; x++) {
			res += prob(t-1, c, o, d, i, s-x)/4;
		}
	} else if (c > 0) {
		for (int x = 1; x <= 6; x++) {
			res += prob(t, c-1, o, d, i, s-x)/6;
		}
	} else if (o > 0) {
		for (int x = 1; x <= 8; x++) {
			res += prob(t, c, o-1, d, i, s-x)/8;
		}
	} else if (d > 0) {
		for (int x = 1; x <= 12; x++) {
			res += prob(t, c, o, d-1, i, s-x)/12;
		}
	} else if (i > 0) {
		for (int x = 1; x <= 20; x++) {
			res += prob(t, c, o, d, i-1, s-x)/20;
		}
	} else {
		res = 1;
	}
	return res;
}

int main() {
	int t, c, o, d, i;
	cin >> t >> c >> o >> d >> i;
	
	vector<pair<double,int>> a;
	for (int s = 0; s < 1000; s++) {
		double p = prob(t, c, o, d, i, s);
		if (p > 0) a.emplace_back(p, s);
	}
	sort(begin(a), end(a), greater<pair<double,int>>());
	for (auto [_,x]: a) cout << x << ' ';
	cout << '\n';
}
