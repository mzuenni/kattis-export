#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

#define sz(a) ((a).size())
#define all(a) (a).begin(), (a).end()

using u64 = uint64_t;
using i64 = int64_t;

constexpr u64 oo = 0x3f3f3f3f3f3f3f3f;

using pii = pair<u64, u64>;

template <typename T>
bool mmin(T& l, const T& r)
{
	if (r < l)
		return l = r, true;
	return false;
}

mt19937 gen { 42 };

u64 solve(const vector<vector<pii>>& g, const vector<u64>& ts, int num_init = 1)
{
	const u64 n = sz(g);
	if (n == 1)
		return 0;
	assert(sz(ts) >= num_init);
	vector<u64> pred(n, -1), dist;
	u64 ans = oo;
	for (u64 rr = 0; rr < 128; rr++) {
		u64 res = 0;
		vector<bool> in_tree(n, false);
		for (u64 i = 0; i < num_init; i++)
			in_tree[ts[i]] = true;
		vector<u64> remaining(ts.begin() + num_init, ts.end());
		for (u64 i = num_init; i < ts.size(); i++) {
			std::swap(remaining.back(), remaining[uniform_int_distribution<u64>(0, remaining.size() - 1)(gen)]);
			const u64 start = remaining.back();
			remaining.pop_back();
			if (in_tree[start])
				continue;

			dist.assign(n, oo);
			priority_queue<pair<i64, u64>> pq;
			dist[start] = 0, pq.emplace(0, start);

			u64 j;
			while (true) {
				i64 d;
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
				if (j == start)
					break;
			}
		}
		ans = min(ans, res);
	}
	return ans;
}

int main()
{
	u64 n, m, v, k;
	cin >> n >> m >> v >> k;
	vector<vector<vector<pii>>> gs(v);
	vector<u64> u(v), s(1);
	for (u64 i = 0; i < v; i++) {
		cin >> u[i];
		gs[i].resize(u[i]);
		s.emplace_back(s.back() + u[i]);
	}
	vector<u64> next(v, oo);
	const auto get_v = [&](u64 i) -> u64 {
		return distance(s.begin(), prev(upper_bound(all(s), i)));
	};
	for (u64 a, b, c; m-- > 0;) {
		cin >> a >> b >> c;
		a--, b--;
		const auto u_v = get_v(a), v_v = get_v(b);
		if (u_v == v_v) {
			gs[u_v][a - s[u_v]].emplace_back(b - s[u_v], c);
			gs[u_v][b - s[u_v]].emplace_back(a - s[u_v], c);
		} else
			mmin(((u_v + 1) % v == v_v) ? next[u_v] : next[v_v], c);
	}
	vector<set<u64>> terminals(v);
	for (u64 m = k, x; m-- > 0;) {
		cin >> x;
		x--;
		terminals[get_v(x)].emplace(x - s[get_v(x)]);
	}

	vector<u64> conn_l(v), conn_r(v), conn_both(v), conn_lr(v);
	u64 res = oo;
	for (u64 i = 0; i < v; i++) {
		vector<u64> tmp(all(terminals[i]));
		if (sz(terminals[i]) == k)
			res = min(res, solve(gs[i], tmp));

		if (not terminals[i].count(0))
			tmp.insert(tmp.begin(), 0);
		conn_l[i] = solve(gs[i], tmp);

		if (not terminals[i].count(u[i] - 1))
			tmp.insert(tmp.begin(), u[i] - 1);
		conn_both[i] = solve(gs[i], tmp);
		conn_lr[i] = solve(gs[i], tmp, 2);

		if (not terminals[i].count(0))
			tmp.erase(find(all(tmp), 0));
		conn_r[i] = solve(gs[i], tmp);
	}

	for (u64 i = 0; i < v; i++) {
		// cut before i
		u64 tmp = conn_r[i];
		for (u64 x = k - sz(terminals[i]), j = 1; j < v and x > 0; j++) {
			tmp += next[(i + j - 1) % v];
			const auto ii = (i + j) % v;
			tmp += (x == sz(terminals[ii])) ? conn_l[ii] : conn_both[ii];
			x -= sz(terminals[ii]);
		}
		res = min(res, tmp);

		// cut in i
		tmp = conn_lr[i];
		for (u64 j = 1; j < v; j++)
			tmp += conn_both[(i + j) % v];
		tmp = accumulate(all(next), tmp);
		res = min(res, tmp);
	}
	cout << res << endl;
}
