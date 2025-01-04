#include <bits/stdc++.h>
using namespace std;

map<char, char> fh = { { 'b', 'd' }, { 'd', 'b' }, { 'q', 'p' }, { 'p', 'q' } };
map<char, char> fv = { { 'b', 'p' }, { 'p', 'b' }, { 'q', 'd' }, { 'd', 'q' } };

char flip_char(char u, string &t) {
	for (char c: t) {
		switch(c) {
			case 'h':
				u = fh[u];
				break;
			case 'v':
				u = fv[u];
				break;
			case 'r':
				u = fh[fv[u]];
				break;
		}
	}
	return u;
}

map<char, char> find_flips(string &t) {
	map<char, char> flips;
	string bbq = "bqdp";
	
	for (char c: bbq) flips[c] = flip_char(c, t);
	return flips;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	string s, t;
	cin >> s >> t;
	int n = (int) s.size();

	map<char, char> flips = find_flips(t);
	for (int i = 0; i < n; i++) s[i] = flips[s[i]];
	if ((t.size() + count(t.begin(), t.end(), 'v')) & 1) {
		reverse(s.begin(), s.end());
	}

	cout << s << endl;
}
