#include <bits/stdc++.h>
// @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED

struct d {
	int l, r, c;
};

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::set<std::pair<int, int>> seen;
	std::deque<d> q;

	q.push_back({ 0, 0, 0 });

	std::vector<int> nseen(n + 1);

	while (true) {
		d p = q.front();
		q.pop_front();

		if (seen.find(std::make_pair(p.l, p.r)) != seen.end()) {
			continue;
		}

		seen.insert(std::make_pair(p.l, p.r));

		if (p.l + p.r == n) {
			std::cout << p.c << std::endl;
			return 0;
		}

		if (nseen[p.l + p.r] >= 6) {
			continue;
		}
		++nseen[p.l + p.r];

		// l
		if (a[p.l] == p.l + p.r + 1) {
			q.push_front({ p.l + 1, p.r, p.c });
		} else {
			q.push_back({ p.l + 1, p.r, p.c + 1 });
		}

		// r
		if (a[n - p.r - 1] == p.l + p.r + 1) {
			q.push_front({ p.l, p.r + 1, p.c });
		} else {
			q.push_back({ p.l, p.r + 1, p.c + 1 });
		}
	}
}
