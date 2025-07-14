// @EXPECTED_RESULTS@: WRONG_ANSWER, TIME_LIMIT_EXCEEDED
// 
#include <cassert>
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

		vector<bool> is_terminal(n);
		for (auto t : tts)
			is_terminal[t] = true;

		vector<int> tree_nodes;
		vector<bool> in_tree(n, false);
		{
			auto start = tts[uniform_int_distribution<size_t>(0, tts.size() - 1)(gen)];
			tree_nodes.emplace_back(start);
			is_terminal[start] = false;
			in_tree[start] = true;
		}
		vector<int> pred(n, -1), dist;
		for (int num_in_tree = 1; num_in_tree < k;) {
			dist.assign(n, oo);
			priority_queue<pair<int, int>> pq;
			for (auto k : tree_nodes)
				pq.emplace(dist[k] = 0, k);

			int j;
			while (true) {
				int d;
				tie(d, j) = pq.top();
				pq.pop();
				if (dist[j] != (d = -d))
					continue;
				if (is_terminal[j])
					break;
				for (auto [k, e] : g[j])
					if (dist[k] > d + e)
						pq.emplace(-(dist[k] = d + e), k), pred[k] = j;
			}

			assert(is_terminal[j]);

			res += dist[j];
			for (; not in_tree[j]; j = pred[j]) {
				if (is_terminal[j])
					is_terminal[j] = false, num_in_tree++;
				in_tree[j] = true;
				tree_nodes.emplace_back(j);
			}
		}

		ans = min(ans, res);

		const auto end = chrono::steady_clock::now();
		const chrono::duration<double, milli> diff = end - start;
		if (diff.count() >= 900)
			break;
	}
	cout << ans << endl;
}
