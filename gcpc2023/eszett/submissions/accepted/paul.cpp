#include <iostream>
#include <string>
using namespace std;

int main() {
	string s; cin >> s;
	for (char &c: s) c = tolower(c);
	cout << s << '\n';

	size_t i = s.find("sss");
	if (i != string::npos) {
		for (string t: {"sB", "Bs"}) {
			cout << s.substr(0, i) << t << s.substr(i+3) << '\n';
		}
	} else {
		i = s.find("ss");
		if (i != string::npos) {
			cout << s.substr(0, i) << "B" << s.substr(i+2) << '\n';
		}
	}
}
