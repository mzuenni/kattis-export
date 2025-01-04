#include <cstdint>
#include <cstring>
#include <iostream>
#include <set>
#include <array>

#define sz(a) ((int)(a).size())

using namespace std;

multiset<int> cards[3];

constexpr bool step(bool cur, uint8_t c) {
	return array<bool,3>{false, cur, !cur}[c];
}

uint8_t dp[2][2][301][301][301];
uint8_t ans(bool cur, bool tar, array<int, 3> num) {
	uint8_t& res = dp[cur][tar][num[0]][num[1]][num[2]];
	if (res < 0xff) return res;
	for (uint8_t i = 0; i < 3; i++) {
		if (num[i]-- > 0 and ans(step(cur, i), !tar, num) == 0)
			return res = i + 1;
		num[i]++;
	}
	return res = 0;
}

int main() {
	memset(dp, 0xff, sizeof(dp));
	dp[0][1][0][0][0] = dp[1][0][0][0][0] = 0;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char c; int num;
		cin >> c >> num;
		cards[(c=='+') + (num%2)].emplace((c=='+' ? 1 : -1) * num);
	}
	cin >> n; n %= 2;

	array<int,3> cnt{sz(cards[0]), sz(cards[1]), sz(cards[2])};
	bool me = (ans(n, true, cnt) != 0), cur = n;
	cout << (me ? "me" : "you") << endl;

	const bool tar = me;
	while (cnt != array<int,3>{0,0,0}) {
		int idx;
		if (not me) {
			char c; int num;
			cin >> c >> num;
			idx = (c == '+') + (num % 2);
			cards[idx].erase(cards[idx].find((c=='+' ? 1 : -1) * num));
		} else {
			idx = ans(cur, tar, cnt) - 1;
			auto x = *cards[idx].begin();
			cards[idx].erase(cards[idx].begin());
			cout << (x < 0 ? "* " : "+ ") << abs(x) << endl;
		}
		me ^= 1, cur = step(cur, idx), cnt[idx]--;
	}
}
