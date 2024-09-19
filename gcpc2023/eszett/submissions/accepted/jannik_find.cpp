#include <iostream>

using namespace std;

int main() {
	string s;
	cin >> s;
	for (char& c : s) c = tolower(c);
	cout << s << endl;
	size_t p = 0;
	while (true) {
		const size_t np = s.find("ss", p);
		if (np >= s.size()) break;
		cout << s.substr(0, np) << 'B' << s.substr(np+2) << endl;
		p = np + 1;
	}
	return 0;
}
