#include <iostream>
#include <set>
#include <stack>

using namespace std;

void fail() {
	cout << "no\n";
	exit(0);
}

int main()
{
	int n;
	cin >> n;
	set<string> seen;
	stack<string> s;
	while (n-- > 0) {
		string a, b;
		cin >> a >> b;
		if (a == "pickup") {
			if (not seen.emplace(b).second)
				fail();
			s.emplace(b);
		} else {
			if (s.empty() or s.top() != b)
				fail();
			else
				s.pop();
		}
	}
	cout << (s.empty() ? "yes\n" : "no\n");
}
