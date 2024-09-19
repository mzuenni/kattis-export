#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, q;
	cin >> n >> q;

	set<int> closed;

	auto solve = [&](int a, int b) {
		if (a > b) swap(a,b);
		if (closed.empty()) return true;
		if (closed.contains(a) || closed.contains(b)) return false;
		auto it = closed.lower_bound(a);
		if (it == end(closed) || *it > b) return true;
		if (*begin(closed) > a && *rbegin(closed) < b) return true;
		return false;
	};

	while (q--) {
		char c; cin >> c;
		if (c == '?') {
			int a, b;
			cin >> a >> b;
			cout << (solve(a,b) ? "possible" : "impossible") << '\n';
		} else if (c == '-') {
			int a; cin >> a;
			closed.insert(a);
		} else if (c == '+') {
			int a; cin >> a;
			closed.erase(a);
		} else {
			assert(0);
		}
	}
}
