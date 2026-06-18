#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

#define int int64_t
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

using pii = pair<int, int>;

signed main()
{
	int n;
	cin >> n;

	map<int, vector<pii>, greater<>> cities;
	for (int i = 0, d, a, c; i < 2 * n; i++) {
		cin >> d >> a >> c;
		cities[c].emplace_back(d, a);
	}
	cities[0];

	priority_queue<int> f_gain, s_gain;
	int score = 0;
	for (auto& [c, r] : cities) {
		if (c == 0)
			assert(sz(r) % 2 == 0);
		sort(all(r), [](pii l, pii r) {
			return l.second - l.first > r.second - r.first;
		});
		int i;
		for (i = 0; i < sz(r) / 2; i++) {
			score += r[i].second;
			s_gain.emplace(r[i].first - r[i].second - c);
		}
		if (sz(r) % 2) {
			cities[0].emplace_back(r[i]);
			r.erase(r.begin() + i);
		}
		assert(sz(r) % 2 == 0);
		for (; i < sz(r); i++) {
			score += r[i].first;
			f_gain.emplace(r[i].second - r[i].first - c);
		}
		score += c * sz(r) / 2;
	}
	assert(sz(f_gain) == sz(s_gain));
	while (not f_gain.empty() and not s_gain.empty() and f_gain.top() + s_gain.top() > 0) {
		score += s_gain.top() + f_gain.top();
		s_gain.pop(), f_gain.pop();
	}

	cout << score << endl;
}
