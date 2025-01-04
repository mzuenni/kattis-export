#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include <span>

using namespace std;

using ll = long long;

#define sz(a) ((ll)(a).size())
#define all(a) (a).begin(),(a).end()

vector<ll> pre(span<ll> s) {
	vector<ll> res(sz(s));
	vector<ll> last(256, -1);
	for (ll i = 0; i < sz(s); i++) {
		if (s[i] < 0)
			res[i] = s[i];
		else {
			if (last[s[i]] != -1)
				res[i] = i - last[s[i]];
			last[s[i]] = i;
		}
	}
	return res;
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);

	auto read = [&] {
		string tmp;
		getline(cin, tmp); // n
		getline(cin, tmp);
		vector<ll> res(sz(tmp));
		for (ll i = 0; i < sz(tmp); i++) {
			if ((i == 0 or isspace(tmp[i-1])) and (i+1==sz(tmp) or isspace(tmp[i+1])))
				res[i] = tmp[i];
			else
				res[i] = -tmp[i];
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
	string tmp; getline(cin, tmp);
	while (q-- > 0) {
		auto tmp = read();
		const auto p = pre(span<ll>{tmp.data(), tmp.size()});
		auto it = lower_bound(all(suffixes), p);
		cout << (it != suffixes.end() and it->size() >= sz(p) and equal(all(p), it->begin()) ? "yes\n" : "no\n");
	}
	return 0;
}
