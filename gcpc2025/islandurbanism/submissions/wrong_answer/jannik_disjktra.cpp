#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

using namespace std;

#define int int64_t

constexpr int oo = 0x3f3f3f3f3f3f3f3f;

signed main()
{
	const auto start = chrono::steady_clock::now();

	int n, m, v, k;
	cin >> n >> m >> v >> k;
	// ignore u
	for (int i = 0, x; i < v; i++)
		cin >> x;

	vector<vector<pair<int, int>>> g(n);
	while (m-- > 0) {
		int a, b, c;
		cin >> a >> b >> c;
		g[--a].emplace_back(--b, c);
		g[b].emplace_back(a, c);
	}

	vector<int> tts(k);
	for (int& x : tts)
		cin >> x, x--;

	int ans = oo;

	mt19937 gen(42);

	// start with a random terminal, then add the others to the tree via dijkstra
	while (true) {
		int res = 0;

		auto ts = tts;
		const auto choose = [&] {
			std::swap(ts.back(), ts[uniform_int_distribution<size_t>(0, ts.size() - 1)(gen)]);
		};

		vector<int> tree_nodes;
		vector<bool> in_tree(n, false);
		choose();
		tree_nodes.emplace_back(ts.back());
		in_tree[ts.back()] = true;
		ts.pop_back();
		vector<int> pred(n, -1), dist;
		while (not ts.empty()) {
			choose();
			if (in_tree[ts.back()]) {
				ts.pop_back();
				continue;
			}

			dist.assign(n, oo);
			priority_queue<pair<int, int>> pq;
			dist[ts.back()] = 0, pq.emplace(0, ts.back());

			int j;
			while (true) {
				int d;
				tie(d, j) = pq.top();
				pq.pop();
				if (dist[j] != (d = -d))
					continue;
				if (in_tree[j])
					break;
				for (auto [k, e] : g[j])
					if (dist[k] > d + e)
						pq.emplace(-(dist[k] = d + e), k), pred[k] = j;
			}

			res += dist[j];
			for (j = pred[j];; j = pred[j]) {
				in_tree[j] = true;
				tree_nodes.emplace_back(j);
				if (j == ts.back())
					break;
			}

			ts.pop_back();
		}

		ans = min(ans, res);

		const auto end = chrono::steady_clock::now();
		const chrono::duration<double, milli> diff = end - start;
		if (diff.count() >= 900)
			break;
	}
	cout << ans << endl;
}
