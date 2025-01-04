#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <span>

using namespace std;

using ll = long long;

#define sz(a) ((ll)(a).size())
#define all(a) (a).begin(),(a).end()

vector<ll> pre(span<ll> s) {
	vector<ll> res(sz(s));
	unordered_map<ll, ll> last;
	for (ll i = 0; i < sz(s); i++) {
		if (s[i] < 0) {
			auto[it, succ] = last.emplace(s[i], i);
			if (not succ)
				res[i] = i - it->second;
			it->second = i;
		} else
			res[i] = -s[i] - 1;
	}
	return res;
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);

	unordered_map<string, ll> tokens;
	auto lookup = [&](const std::string& s) {
		auto[it,succ] = tokens.emplace(s, sz(tokens));
		return sz(s) == 1 and isalpha(s[0]) ? -it->second - 1 : it->second;
	};
	auto read = [&] {
		ll n; cin >> n;
		vector<ll> res(n);
		string tmp;
		for (auto& s : res) {
			cin >> tmp;
			s = lookup(tmp);
		}
		return res;
	};
	auto code = read();
	vector<vector<ll>> suffixes;
	for (ll i = 0; i < sz(code); i++)
		suffixes.emplace_back(pre(span<ll>{code.begin() + i, code.end()}));

	sort(all(suffixes));
	
	ll q;
	cin >> q;
	while (q-- > 0) {
		auto tmp = read();
		const auto p = pre(span<ll>{tmp.data(), tmp.size()});
		auto it = lower_bound(all(suffixes), p);
		cout << (it != suffixes.end() and it->size() >= sz(p) and equal(all(p), it->begin()) ? "yes\n" : "no\n");
	}
	return 0;
}
