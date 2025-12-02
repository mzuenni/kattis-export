#include <bits/stdc++.h>

constexpr int N = 600000;
int nn;
int t[2 * N];
int blocksize = 700;

void modify(int p, int value) {
	for (int i = p; i < nn; i += blocksize) {
		t[i] = std::max(t[i], value);
	}
}

int query(int l, int r) {
	int ans = 0;
	for (int i = std::max(0, r - blocksize); i < r; ++i) {
		ans = std::max(ans, t[i]);
	}
	return ans;
}

int main() {
	int n;
	std::cin >> n;
	nn = n + 2;
	std::vector<int> a(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<std::vector<int>> right(n + 1), down(n + 1);

	for (int i = 0; i < n; ++i) {
		// if we put it on the left, we need to put a[i] - i - 1 things on the right and (including it) i + 1 things on the left
		int l = i + 1;
		int r = a[i] - i - 1;

		if (r >= 0) {
			down[l].push_back(r);
		}

		// if we put it on the right, we need to put n - i things (including it) on the right and a[i] - n + i things on the left
		l = a[i] - n + i;
		r = n - i;
		if (l >= 0) {
			right[l].push_back(r);
		}
	}

	for (int l = 0; l <= n; ++l) {
		// process incoming down arrows
		std::sort(down[l].begin(), down[l].end(), std::greater<>());

		for (int r : down[l]) {
			int best = query(0, r + 1);
			modify(r, best + 1);
		}

		// process right arrows
		std::sort(right[l].begin(), right[l].end());

		for (int r : right[l]) {
			int best = query(0, r);
			modify(r, best + 1);
		}

	}

	int ans = n - query(0, n + 1);

	std::cout << ans << std::endl;
}
