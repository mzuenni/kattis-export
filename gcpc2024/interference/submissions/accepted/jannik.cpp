#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

using i64 = int64_t;

int main() {
	i64 n, w;
	cin >> n >> w;
	vector<tuple<i64,i64,i64>> waves;
	vector<i64> res;
	while (n-- > 0) {
		char c;
		i64 p, l, a;
		cin >> c >> p;
		if (c == '!') {
			cin >> l >> a;
			waves.emplace_back(p,l,a);
		} else {
			i64 sum = 0;
			for (auto[p1,l,a] : waves) {
				if (p1 > p or p1 + l <= p or (p - p1) % 2 == 1)
					continue;
				sum -= (((p - p1) % 4) - 1) * a;
			}
			res.emplace_back(sum);
		}
	}
	// cout << res.size() << '\n';
	for (i64 x : res)
		cout << x << '\n';
}
