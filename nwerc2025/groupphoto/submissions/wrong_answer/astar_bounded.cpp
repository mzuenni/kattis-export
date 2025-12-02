#include <bits/stdc++.h>

/*
 * This solution does A* search on the DP space, using the admissible heuristic
 * given my `max(0, n - i - j - <number of zero-cost edges in the quarter-plane [i, ∞) × [j, ∞)>)`.
 *
 * To efficiently compute the heuristic, we use a segment using the "saving the entire subarray
 * in each vertex" technique.
 *
 * This solution is of course strictly more complicated than the intended solution and
 * it's pretty easy to see that it has no chance of passing within the time limit.
 */

constexpr int N = 500005;
int n, nn;
std::vector<int> t[2 * N];

void insert(int p, int value) {
	p += nn;
	t[p].push_back(value);
	for (; p > 1; p >>= 1) t[p >> 1].push_back(value);
}

void lock() {
	for (int i = 0; i < 2 * N; ++i) {
		std::sort(t[i].begin(), t[i].end());
	}
}

// Returns the number of points (x, y) with x in [l, r) and y >= b
int query(int l, int r, int b) {
	int res = 0;
	for (l += nn, r += nn; l < r; l >>= 1, r >>= 1) {
		if (l & 1) {
			res += std::distance(std::lower_bound(t[l].begin(), t[l].end(), b), t[l].end());
			++l;
		}
		if (r & 1) {
			--r;
			res += std::distance(std::lower_bound(t[r].begin(), t[r].end(), b), t[r].end());
		}
	}
	return res;
}

struct d {
	long long l, r, c, h;
};

d mkd(long long l, long long r, long long c) {
	long long remaining = n - l - r;
	long long approx = std::max(0ll, remaining - query(l, nn, r));
	return { l, r, c, c + approx };
}

long long score(const d &p) {
	int depth = p.l + p.r;
	return - depth - p.c;
}

bool operator<(const d &l, const d &r) {
	return r.h < l.h;
}

int main() {
	std::cin >> n;
	nn = n + 2;
	std::vector<int> a(n);

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		int j = a[i - 1] - i;
		if (j >= 0) {
			insert(i - 1, j);
		}
	}
	for (int j = 1; j <= n; ++j) {
		int i = a[n - j] - j;
		if (i >= 0) {
			insert(i, j - 1);
		}
	}
	lock();

	std::set<std::pair<int, int>> seen;
	std::priority_queue<d> q;

	q.push(mkd(0, 0, 0));

	std::vector<int> nseen(n + 1);

	while (true) {
		d p = q.top();
		q.pop();

		if (seen.find(std::make_pair(p.l, p.r)) != seen.end()) {
			continue;
		}

		seen.insert(std::make_pair(p.l, p.r));

		if (p.l + p.r == n) {
			std::cout << p.c << std::endl;
			return 0;
		}

		if (nseen[p.l + p.r] >= 2ll) {
			continue;
		}
		++nseen[p.l + p.r];

		// l
		if (a[p.l] == p.l + p.r + 1) {
			q.push(mkd(p.l + 1, p.r, p.c));
		} else {
			q.push(mkd(p.l + 1, p.r, p.c + 1));
		}

		// r
		if (a[n - p.r - 1] == p.l + p.r + 1) {
			q.push(mkd(p.l, p.r + 1, p.c));
		} else {
			q.push(mkd(p.l, p.r + 1, p.c + 1));
		}
	}
}
