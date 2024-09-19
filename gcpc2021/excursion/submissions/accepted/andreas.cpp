#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e9;

struct Edge {
	long long j, d, t;
	Edge(long long j = -1, long long d = 0, long long t = 0): j(j), d(d), t(t) {}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	long long n, m;
	cin >> n >> m;
	vector<Edge> to_insert(m);
	for (long long i = 0; i < m; i++) {
		long long j, d, t;
		cin >> j >> d >> t;
		j--;
		Edge edge(j, d, t);
		to_insert[i] = edge;
	}
	sort(to_insert.begin(), to_insert.end(), [&](Edge a, Edge b) {
			return a.t > b.t;
	});

	vector<long long> cur_dist(n - 1);
	for (long long i = 0; i < n - 1; i++) cur_dist[i] = INF;

	long long q;
	cin >> q;
	vector<long long> queries(q), idx_queries(q);
	for (long long i = 0; i < q; i++) {
		idx_queries[i] = i;
		cin >> queries[i];
	}
	sort(idx_queries.begin(), idx_queries.end(), [&](const long long i, const long long j) {
		return queries[i] > queries[j];
	});

	vector<bool> cross(n - 1);
	long long amount_to_cross = 0;

	vector<long long> result(q, -1);

	long long verb = 0;
	long long dist = accumulate(cur_dist.begin(), cur_dist.end(), 0LL);
	for (long long j = 0; j < q; j++) {
		while (verb < m && to_insert[verb].t >= queries[idx_queries[j]]) {
			if (cur_dist[to_insert[verb].j] > to_insert[verb].d) {
				if (cross[to_insert[verb].j] == false) {
					cross[to_insert[verb].j] = true;
					amount_to_cross++;
				}
				long long dif = cur_dist[to_insert[verb].j] - to_insert[verb].d;
				cur_dist[to_insert[verb].j] -= dif;
				dist -= dif;
			}
			verb++;
			assert(amount_to_cross <= n - 1);
		}

		if (amount_to_cross == n - 1) {
			result[idx_queries[j]] = dist;
		}
	}

	for (long long i = 0; i < q; i++) {
		if (result[i] == -1) cout << "impossible" << endl;
		else cout << result[i] << endl;
	}
}
