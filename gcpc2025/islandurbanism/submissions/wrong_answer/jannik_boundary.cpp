#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

using namespace std;

#define sz(a) ((a).size())
#define all(a) (a).begin(), (a).end()

using u64 = uint64_t;

constexpr u64 oo = 0x3f3f3f3f3f3f3f3f;

using pii = pair<u64, u64>;

template <typename T>
bool mmin(T& l, const T& r)
{
	if (r < l)
		return l = r, true;
	return false;
}

// n * 3^k + m * log n * 2^k
vector<u64> solve(const vector<vector<pii>>& g, const vector<u64>& terminals)
{
	const u64 n = sz(g);
	vector<u64> mem(n * (1u << sz(terminals)), oo);
	const auto dp = [&](u64 i, u64 S) -> u64& {
		return mem[S * n + i];
	};
	vector<u64> is_terminal(n);
	for (u64 i = 0; i < sz(terminals); i++)
		is_terminal[terminals[i]] = 1u << i;
	for (u64 i = 0; i < n; i++)
		dp(i, 0) = 0;
	for (u64 S = 1; S < (1u << sz(terminals)); S++) {
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		for (u64 i = 0; i < n; i++) {
			if ((S & is_terminal[i]) != 0)
				mmin(dp(i, S), dp(i, S ^ is_terminal[i]));
			for (u64 S2 = (S - 1) & S; S2 != 0; S2 = (S2 - 1) & S)
				mmin(dp(i, S), dp(i, S2) + dp(i, S ^ S2));
			if (dp(i, S) < oo)
				pq.emplace(dp(i, S), i);
		}
		while (not pq.empty()) {
			auto [v, i] = pq.top();
			pq.pop();
			if (dp(i, S) != v)
				continue;
			for (auto [j, c] : g[i])
				if (mmin(dp(j, S), dp(i, S) + c))
					pq.emplace(dp(j, S), j);
		}
	}
	return mem;
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
		auto tmp = terminals[i];
		tmp.insert({ 0, u[i] - 1 });
		const u64 k_v = sz(tmp), n = sz(gs[i]);
		const u64 first = ~(u64)!terminals[i].count(0);
		const u64 last = ~((1ull << (k_v - 1)) * !terminals[i].count(n - 1));
		const auto dp = solve(gs[i], vector<u64>(all(tmp)));
		const u64 everyone = (1u << k_v) - 1;
		conn_both[i] = dp[n * everyone + 0];
		conn_r[i] = dp[n * (everyone & first) + n - 1];
		conn_l[i] = dp[n * (everyone & last) + 0];
		if (sz(terminals[i]) == k)
			res = min(res, dp[n * (everyone & first & last) + 0]);
		conn_lr[i] = conn_both[i];
		for (u64 mask = (1ull << (k_v - 1)); mask < (1u << k_v); mask += 2)
			mmin(conn_lr[i], dp[n * mask + n - 1] + dp[n * (everyone ^ mask) + 0]);
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
