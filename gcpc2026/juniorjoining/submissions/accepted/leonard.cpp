#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int K = 1e6 + 5;

int main() {
	int n;
	std::cin >> n;

	std::vector<std::vector<std::pair<int, int>>> recs(K);

	for (int i = 0; i < 2 * n; ++i) {
		int l, r, c;
		std::cin >> l >> r >> c;
		recs[c].emplace_back(l, r);
	}

	long long ans = 0;

	std::multiset<int> al, ar;

	for (int c = 0; c < K; ++c) {
		if (recs[c].empty()) continue;
		std::vector<int> vl, vr;
		for (auto [l, r] : recs[c]) {
			if (l >= r) {
				ans += l;
				vl.push_back(l - r);
			}
			else {
				ans += r;
				vr.push_back(r - l);
			}
		}
		std::sort(vl.rbegin(), vl.rend());
		std::sort(vr.rbegin(), vr.rend());
		while (vl.size() >= vr.size() + 2 && vl.back() < c) {
			int x = vl.back();
			vl.pop_back();
			ans -= x;
			vr.push_back(-x);
		}
		while (vr.size() >= vl.size() + 2 && vr.back() < c) {
			int x = vr.back();
			vr.pop_back();
			ans -= x;
			vl.push_back(-x);
		}
		std::sort(vl.begin(), vl.end());
		std::sort(vr.begin(), vr.end());
		int szl = vl.size();
		int szr = vr.size();
		if (szl >= szr) {
			int k = (szl - szr) / 2;
			ans += 1LL * szr * c;
			for (int i = 0; i < k; ++i) {
				vl[i] -= c;
			}
			for (int i = 1; i <= szr + k; ++i) {
				vl[vl.size() - i] += c;
			}
			for (int i = 0; i < szr; ++i) {
				vr[i] += c;
			}
		}
		else {
			int k = (szr - szl) / 2;
			ans += 1LL * szl * c;
			for (int i = 0; i < k; ++i) {
				vr[i] -= c;
			}
			for (int i = 1; i <= szl + k; ++i) {
				vr[vr.size() - i] += c;
			}
			for (int i = 0; i < szl; ++i) {
				vl[i] += c;
			}
		}
		for (int x : vl) {
			al.insert(x);
		}
		for (int x : vr) {
			ar.insert(x);
		}
	}

	while (al.size() > ar.size()) {
		int x = *al.begin();
		al.erase(al.begin());
		ans -= x;
		ar.insert(-x);
	}

	while (ar.size() > al.size()) {
		int x = *ar.begin();
		ar.erase(ar.begin());
		ans -= x;
		al.insert(-x);
	}

	while (*al.begin() + *ar.begin() < 0) {
		int x = *al.begin();
		int y = *ar.begin();
		al.erase(al.begin());
		ar.erase(ar.begin());
		ar.insert(-x);
		al.insert(-y);
		ans -= x;
		ans -= y;
	}

	std::cout << ans << '\n';

	return 0;
}
