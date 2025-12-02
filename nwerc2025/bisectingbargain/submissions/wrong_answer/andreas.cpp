#include <iostream>
#include <vector>
#include <numeric>
#include <assert.h>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;
	vector<int> coins = { 500, 200, 100, 50, 20, 10, 5, 2, 1 };

	int rep = 100;
	while (rep--) {
		int x = n;
		vector<int> res;
		for (int c: coins) if (c <= x) {
			int am = (c == 1 ? x : rand() % (x/c+1));
			x -= am * c;
			while (am--) res.push_back(c);
		}

		assert (accumulate(res.begin(), res.end(), 0) == n);
		vector<bool> dp(n/2+1);
		dp[0] = true;
		for (int c: res) for (int i = n/2 - c; i >= 0; i--) {
			if (dp[i]) dp[i+c] = true;
		}
		if (n % 2 == 1 || !dp[n/2]) {
			cout << res.size();
			for (int c: res) cout << ' ' << c;
			cout << '\n';
			return 0;
		}
	}
	cout << "splittable" << '\n';

}
