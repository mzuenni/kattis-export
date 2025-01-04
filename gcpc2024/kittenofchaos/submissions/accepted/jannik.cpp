#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr), cout.sync_with_stdio(false);
	string s, t;
	cin >> s >> t;
	int res = 0;
	string vhr = "vhr", bpdq = "bpdq";
	for (char c : t) res ^= 1 + vhr.find_first_of(c);
	for (char& c : s) c = bpdq[bpdq.find_first_of(c) ^ res];
	if (res & 2) reverse(s.begin(), s.end());
	cout << s << '\n';
}
