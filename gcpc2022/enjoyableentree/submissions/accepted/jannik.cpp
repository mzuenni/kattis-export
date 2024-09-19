#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

using ll = long long;

#define sz(a) ll((a).size())

int main() {
	ll n;
	cin >> n;
	n = min(n, 1000ll);

	vector<double> p(max(2ll, n));
	p[0] = 100;
	p[1] = 0;

	for (ll i = 2; i < sz(p); i++)
		p[i] = (p[i-1] + p[i-2]) / 2;

	cout << fixed << setprecision(10) << p[n-1] << ' ' << (100 - p[n-1]) << endl;

	return 0;
}
