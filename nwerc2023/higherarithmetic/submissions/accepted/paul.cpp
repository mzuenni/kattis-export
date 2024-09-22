#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	vector<int> a(n);
	for (int &x: a) cin >> x;

	vector<vector<string>> b(1234567);
	for (int x: a) b[x].push_back(to_string(x));

	auto combine = [&](int i, int j) {
		string s = b[i].back();
		b[i].pop_back();
		string t = b[j].back();
		b[j].pop_back();
		b[i+j].push_back("(" + s + "+" + t + ")");
	};

	while (!b[1].empty()) {
		if (!b[2].empty()) {
			combine(1, 2);
		} else if (b[1].size() > 1) {
			combine(1, 1);
		} else if (n > 1) {
			int k = 2;
			while (b[k].empty()) k++;
			combine(1, k);
		} else {
			break;
		}
	}

	bool first = true;
	for (auto v: b) for (string s: v) {
		if (first) first = false; else cout << '*';
		cout << s;
	}
	cout << '\n';
}
