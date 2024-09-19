#include <iostream>
#include <cmath>

using namespace std;

using ll = long long;

int main() {
	ll a, b;
	cin >> a >> b;
	a--, b--;

	ll res = 0;

	for (ll x = 0; x < a; x++) {
		const ll y = sqrt(a*a - x*x) + .5;
		if (x*x + y*y != a*a)
			continue;
		// (x,y) is edge with length a

		// (y,-x) * b / a should be edge with length b
		// => (x * b / a) and (y * b / a) must be integral
		if ((x * b) % a != 0 && (y * b) % a != 0)
			continue;

		res++;
	}

	if (a != b)
		res *= 2;

	cout << res << endl;

	return 0;
}
