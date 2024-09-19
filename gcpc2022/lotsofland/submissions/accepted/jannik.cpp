#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
	ll h, w, n;
	cin >> h >> w >> n;

	if ((h*w) % n != 0) {
		cout << "impossible\n";
		return 0;
	}

	const ll A = (h*w) / n;

	for (ll a = 1; a <= w; a++) {
		const ll b = A / a;
		if (a*b != A || w%a != 0 || h%b != 0)
			continue;

		for (ll i = 0; i < h; i++) {
			for (ll j = 0; j < w; j++)
				cout << char('A' + (i/b) * (w/a) + j/a);
			cout << '\n';
		}

		return 0;
	}
	return 1;
}
