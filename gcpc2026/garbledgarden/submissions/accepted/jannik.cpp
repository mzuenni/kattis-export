#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vii = vector<pair<int, int>>;

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a.size()))

vector<vi> euler_cycles(vector<vii> g)
{
	const int n = sz(g);
	vector<vi> res;
	for (int i = 0; i < n; i++) {
		if (g[i].empty())
			continue;
		vi path;
		const auto dfs = [&](auto&& self, int i) -> void {
			while (sz(g[i])) {
				auto[k,j] = g[i].back();
				g[i].pop_back();
				self(self, k);
				path.emplace_back(j);
			}
		};
		dfs(dfs, i);
		res.emplace_back(std::move(path));
	}
	return res;
}

int main()
{
	int n;
	cin >> n;
	vector<int> p(n);
	for (int& x : p)
		cin >> x, x--;

	if (is_sorted(all(p))) {
		cout << "0\n";
		return 0;
	}

	vi p_sorted = p;
	sort(all(p_sorted));

	vector<vii> g(n);
	for (int i = 0; i < n; i++)
		if (p[i] != p_sorted[i])
			g[p_sorted[i]].emplace_back(p[i], i);

	auto cycles = euler_cycles(g);
	if (sz(cycles) > 2) {
		vi a, b;
		for (vi& c : cycles) {
			a.insert(a.end(), all(c));
			b.emplace_back(c.back());
		}
		reverse(all(b));
		cycles = {a, b};
	}
	cout << sz(cycles) << '\n';
	for (const vi& c : cycles) {
		cout << sz(c) << '\n';
		for (int i = 0; i < sz(c); i++)
			cout << c[i] + 1 << (i + 1 < sz(c) ? ' ' : '\n');
	}
}
