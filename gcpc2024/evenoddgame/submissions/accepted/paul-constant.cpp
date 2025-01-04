#include <array>
#include <cassert>
#include <iostream>
#include <set>
using namespace std;

int slot(char op, int x) {
	if (op == '+' && x%2 == 1) return 1;
	if (op == '*' && x%2 == 0) return 2;
	return 0;
}

int win(int who, int cur, int a, int b, int c) {
	if (c == 0) return (cur+b) % 2 == who;
	if (who == 0) return true;
	return c == 1 && b%2 == 1;
}

int main() {
	int n; cin >> n;
	array<set<pair<char,int>>,3> ops;
	while (n--) {
		char op; cin >> op;
		int x; cin >> x;
		ops[slot(op, x)].emplace(op, x);
	}

	int a = size(ops[0]), b = size(ops[1]), c = size(ops[2]);

	int cur; cin >> cur;
	cur %= 2;

	int odd = win(1, cur, a, b, c), who = odd;
	cout << (who ? "me" : "you") << endl;

	while (true) {
		a = size(ops[0]), b = size(ops[1]), c = size(ops[2]);
		if (a+b+c == 0) break;
		pair<char,int> move;
		auto &[op, x] = move;
		if (who) {
			if (a > 0 && !win(1-odd, cur, a-1, b, c)) {
				move = *begin(ops[0]);
			} else if (b > 0 && !win(1-odd, 1-cur, a, b-1, c)) {
				move = *begin(ops[1]);
			} else if (c > 0 && !win(1-odd, 0, a, b, c-1)) {
				move = *begin(ops[2]);
			} else {
				assert(0);
			}
			cur = (op == '+' ? cur+x : cur*x) % 2;
			ops[slot(op, x)].erase(move);
			cout << op << ' ' << x << endl;
		} else {
			cin >> op >> x;
			cur = (op == '+' ? cur+x : cur*x) % 2;
			ops[slot(op, x)].erase(move);
		}
        who = 1-who;
	}
}
