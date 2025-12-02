#include <bits/stdc++.h>

int main() {
	int n;
	std::cin >> n;
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

	std::set<std::pair<int, int>> pareto;

	pareto.insert({ 0, 0 });

	for (int l = 0; l <= n; ++l) {
		// process incoming down arrows
		std::sort(down[l].begin(), down[l].end(), std::greater<>());

		for (int r : down[l]) {
			auto itf = pareto.lower_bound({ r + 1, -1 });
			auto itb = itf;
			--itb;
			int newbest = itb->second + 1;
			pareto.insert({ r, newbest });
			if (itb->first == r) pareto.erase(itb);
			if (itf != pareto.end() && itf->second == newbest) pareto.erase(itf);
		}

		// process right arrows
		std::sort(right[l].begin(), right[l].end());

		for (int r : right[l]) {
			auto itf = pareto.lower_bound({ r, -1 });
			auto itb = itf;
			--itb;
			int newbest = itb->second + 1;
			if (itf != pareto.end() && itf->first == r) {
				if (itf->second < newbest) {
					pareto.insert({ r, newbest });
					pareto.erase(itf);
				}
			} else {
				pareto.insert({ r, newbest });
				if (itf != pareto.end() && itf->second == newbest) {
					pareto.erase(itf);
				}
			}
		}

	}

	int ans = n - pareto.rbegin()->second;

	std::cout << ans << std::endl;
}
