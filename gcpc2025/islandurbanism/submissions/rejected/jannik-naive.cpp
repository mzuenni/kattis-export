// @EXPECTED_RESULTS@: RUN_TIME_ERROR, TIME_LIMIT_EXCEEDED

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <queue>
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
vector<pii> solve(const vector<vector<pii>>& g, const vector<u64>& terminals)
{
	const u64 n = sz(g);
	vector<pii> mem(n * (1u << sz(terminals)), pii(oo, -1));
	const auto dp = [&](u64 i, u64 S) -> pii& {
		return mem[S * n + i];
	};
	vector<u64> is_terminal(n);
	for (u64 i = 0; i < sz(terminals); i++)
		is_terminal[terminals[i]] = 1u << i;
	for (u64 i = 0; i < n; i++)
		dp(i, 0).first = 0;
	for (u64 S = 1; S < (1u << sz(terminals)); S++) {
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		for (u64 i = 0; i < n; i++) {
			if (S & is_terminal[i])
				mmin(dp(i, S), dp(i, S ^ is_terminal[i]));
			for (u64 S2 = (S - 1) & S; S2 != 0; S2 = (S2 - 1) & S)
				mmin(dp(i, S), pii(dp(i, S2).first + dp(i, S ^ S2).first, S2));
			if (dp(i, S).first < oo)
				pq.emplace(dp(i, S).first, i);
		}
		while (not pq.empty()) {
			auto [v, i] = pq.top();
			pq.pop();
			if (dp(i, S).first != v)
				continue;
			for (auto [j, c] : g[i])
				if (mmin(dp(j, S), pii(dp(i, S).first + c, (1ull << 63) + i)))
					pq.emplace(dp(j, S).first, j);
		}
	}
	return mem;
}
void extract_edges(const vector<vector<pii>>& g, const vector<u64>& terminals, const vector<pii>& mem, vector<pii>& edges, u64 i, u64 S)
{
	vector<u64> is_terminal(sz(g));
	for (u64 i = 0; i < sz(terminals); i++)
		is_terminal[terminals[i]] = 1u << i;
	const auto dp = [&](u64 i, u64 S) {
		return mem[S * sz(g) + i];
	};
	const auto dfs = [&](auto&& self, u64 i, u64 S) -> void {
		assert(S != (u64)(-1));
		if (S == 0)
			return;
		if ((S & is_terminal[i]) and dp(i, S ^ is_terminal[i]).first == dp(i, S).first) {
			self(self, i, S ^ is_terminal[i]);
			return;
		}
		auto p = dp(i, S).second;
		assert(p != (u64)(-1));
		if (p & (1ull << 63)) {
			const u64 j = p - (1ull << 63);
			const auto edge = *find_if(all(g[i]), [&](auto e) {
				return e.first == j and dp(j, S).first + e.second == dp(i, S).second;
			});
			assert(dp(j, S).first + edge.second == dp(i, S).first);
			edges.emplace_back(i, j);
			self(self, j, S);
			return;
		}
		assert(p != 0 and p != S);
		assert(dp(i, p).first <= dp(i, S).first);
		assert(dp(i, p ^ S).first <= dp(i, S).first);
		self(self, i, p);
		self(self, i, p ^ S);
	};
	dfs(dfs, i, S);
}

int main()
{
	u64 n, m, v, k;
	cin >> n >> m >> v >> k;
	assert(k < 30);
	for (u64 i = 0, x; i < v; i++)
		cin >> x; // discard village sizes
	vector<vector<pii>> g(n);
	while (m-- > 0) {
		u64 u, v, c;
		cin >> u >> v >> c;
		u--, v--;
		g[u].emplace_back(v, c), g[v].emplace_back(u, c);
	}
	vector<u64> terminals(k);
	for (auto& x : terminals) {
		cin >> x;
		x--;
	}
	auto res_ = solve(g, terminals);
	auto* res = res_.data() + ((1u << k) - 1) * n;
	u64 ans = min_element(res, res + n) - res;
	cout << res[ans].first << endl;
	return 0;
	assert(res[ans].first < n);
	// find edges
	vector<pii> edges;
	extract_edges(g, terminals, res_, edges, ans, (1u << k) - 1);
	cout << sz(edges) << '\n';
	for (auto [a, b] : edges)
		cout << a + 1 << ' ' << b + 1 << '\n';
}
