#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

#define all(a) (a).begin(),(a).end()

int main()
{
	int n;
	string cmd, s;
	cin >> cmd >> n >> s;
	if (cmd == "Encode") {
		cout << '2' << s << '\n';
	} else {
		rotate(s.begin(), find(all(s), '2'), s.end());
		cout << s.c_str() + 1 << '\n';
	}
}
