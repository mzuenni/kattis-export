#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <span>

using namespace std;

using ll = long long;

#define sz(a) ((ll)(a).size())

struct trie {
	map<ll, trie*> ch;
};

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
			res[i] = -s[i];
	}
	return res;
}

void insert(trie* t, span<ll> s) {
	for (ll c : pre(s)) {
		if (auto it = t->ch.find(c); it != t->ch.end())
			t = it->second;
		else {
			auto old = t;
			old->ch.emplace(c, t = new trie());
		}
	}
}

bool walk(trie* t, const vector<ll>& p) {
	for (ll c : p) {
		if (auto it = t->ch.find(c); it != t->ch.end())
			t = it->second;
		else
			return false;
	}
	return t;
}

int main() {
	cin.tie(nullptr), ios::sync_with_stdio(false);
	
	trie* t = new trie();
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
	for (ll i = 0; i < sz(code); i++)
		insert(t, span<ll>{code.begin() + i, code.end()});
	
	ll q;
	for (cin >> q; q-- > 0; ) {
		auto tmp = read();
		cout << (walk(t, pre(span<ll>{tmp.data(), tmp.size()})) ? "yes\n" : "no\n");
	}
	return 0;
}
