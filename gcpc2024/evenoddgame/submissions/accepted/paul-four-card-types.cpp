#include <array>
#include <cstring>
#include <cassert>
#include <iostream>
#include <set>
using namespace std;

int slot(char op, int x) {
    return 2 * (op == '+') + x%2;
}

int A, B, C, D;
int dp[133448704];

int win(int who, int cur, int a, int b, int c, int d) {
	int &res = dp[((((who*2 + cur)*(A+1) + a)*(B+1) + b)*(C+1) + c)*(D+1) + d];
	if (res != -1) return res;

	if (a+b+c+d == 0) return res = (who == cur);
	if (a > 0 && !win(1-who, 0,     a-1, b, c, d)) return res = 1;
	if (b > 0 && !win(1-who, cur,   a, b-1, c, d)) return res = 1;
	if (c > 0 && !win(1-who, cur,   a, b, c-1, d)) return res = 1;
	if (d > 0 && !win(1-who, 1-cur, a, b, c, d-1)) return res = 1;
	return res = 0;
}

int main() {
	int n; cin >> n;
	array<set<pair<char,int>>,4> ops;
	while (n--) {
		char op; cin >> op;
		int x; cin >> x;
		ops[slot(op, x)].emplace(op, x);
	}

	A = size(ops[0]), B = size(ops[1]), C = size(ops[2]), D = size(ops[3]);
    memset(dp, -1, sizeof dp);

	int cur; cin >> cur;
	cur %= 2;

	int odd = win(1, cur, A, B, C, D), who = odd;
	cout << (who ? "me" : "you") << endl;

	while (true) {
		int a = size(ops[0]), b = size(ops[1]), c = size(ops[2]), d = size(ops[3]);
		if (a+b+c+d == 0) break;
		pair<char,int> move;
		auto &[op, x] = move;
		if (who) {
			if (a > 0 && !win(1-odd, 0,     a-1, b, c, d)) move = *begin(ops[0]);
			if (b > 0 && !win(1-odd, cur,   a, b-1, c, d)) move = *begin(ops[1]);
			if (c > 0 && !win(1-odd, cur,   a, b, c-1, d)) move = *begin(ops[2]);
			if (d > 0 && !win(1-odd, 1-cur, a, b, c, d-1)) move = *begin(ops[3]);
			cout << op << ' ' << x << endl;
		} else {
			cin >> op >> x;
		}
		cur = (op == '+' ? cur+x : cur*x) % 2;
		ops[slot(op, x)].erase(move);
        who = 1-who;
	}
}
