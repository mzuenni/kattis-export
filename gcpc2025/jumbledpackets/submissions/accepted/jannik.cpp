#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

#define all(a) (a).begin(), (a).end()

// smallest rotation
string canonical(string s)
{
	string res = s;
	for (int i = 1; i < s.size(); i++) {
		rotate(s.begin(), s.begin() + 1, s.end());
		res = min(res, s);
	}
	return res;
}

vector<string> ternary(int n)
{
	set<string> res;
	for (int S = 0; S < (int)(pow(3, n) + 0.5); S++) {
		string s(n, 'A');
		for (int tmp = S, i = 0; i < n; i++, tmp /= 3)
			s[i] = (tmp % 3) + '0';
		if (count(all(s), '0') != n and count(all(s), '1') != n)
			res.emplace(canonical(s));
	}
	return vector<string>(all(res));
}

int main()
{
	int n;
	string cmd, s;
	cin >> cmd >> n >> s;

	if (cmd == "Encode") {
		if (count(all(s), '0') == n or count(all(s), '1') == n) {
		} else if (n < 5) {
			int x = 0;
			for (int i = 0; i < n; i++)
				x += (1 << i) * (s[i] - '0');
			auto ts = ternary(n);
			s = ternary(n)[x];
		} else {
			// encode s[0..2] into s[1..2]
			int x = ((s[0] - '0') * 2 + s[1] - '0') * 2 + s[2] - '0';
			s[0] = '2';
			s[1] = '0' + (x / 3);
			s[2] = '0' + (x % 3);
		}
	} else {
		if (count(all(s), '0') == n or count(all(s), '1') == n) {
		} else if (n < 5) {
			cerr << canonical(s) << endl;
			auto ts = ternary(n);
			int x = find(all(ts), canonical(s)) - ts.begin();
			for (int i = 0; i < n; i++)
				s[i] = '0' + !!(x & (1 << i));
		} else {
			int r = find(all(s), '2') - s.begin();
			while (true)
				if (s[(r + n - 1) % n] == '2') r = (r + n - 1) % n;
				else if (s[(r + n - 2) % n] == '2') r = (r + n - 2) % n;
				else break;
			rotate(s.begin(), s.begin() + r, s.end());
			int x = (s[1] - '0') * 3 + s[2] - '0';
			s[0] = '0' + (x / 4);
			s[1] = '0' + (x % 4) / 2;
			s[2] = '0' + (x % 2);
		}
	}
	cout << s << '\n';
}
