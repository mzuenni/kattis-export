#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	set<pair<ll, ll>> in;
	for (ll x, y; cin >> x >> y;) in.insert({x, y});

	ll res = 0;
	ll notChanged = 0;
	for (; sz(in) > 1;) {
		vector<ll> xs;
		for (auto& [x, y] : in) xs.push_back(x);
		sort(all(xs));

		set<pair<ll, ll>> out;
		notChanged++;
		for (auto [x, y] : in) {
			if (x == xs[0] && x != xs[1]) {//move single spike inwards
				res += abs(x - xs[1]);
				x = xs[1];
				notChanged = 0;
			}
			out.insert({-y, x});//rotate 90°
		}
		if (notChanged >= 4) break;
		in = out;
	}

	auto [minX, minY] = *in.begin();
	auto [maxX, maxY] = *in.begin();
	for (auto& [x, y] : in) {
		minX = min(minX, x);
		maxX = max(maxX, x);
		minY = min(minY, y);
		maxY = max(maxY, y);
	}
	ll w = maxX - minX;
	ll h = maxY - minY;
	res += 2 * (w + h);//bounding rectangle

	for (auto [x, y] : in) {
		if (x == minX || x == maxX || y == minY || y == maxY) continue;
		res += min(w, h);//point not on bounding box
	}
	cout << res << endl;

}
