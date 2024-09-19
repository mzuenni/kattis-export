#include <bits/stdc++.h>
using namespace std;

bool is_vowel(char c) {
	c = tolower(c);
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
	string s; cin >> s;
	while (!is_vowel(s.back())) s.pop_back();
	cout << s << "ntry" << endl;
}
