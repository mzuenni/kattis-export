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
	set<string> seen, picked_up;
	while (n-- > 0) {
		string a, b;
		cin >> a >> b;
		if (a == "pickup") {
			if (not seen.emplace(b).second)
				fail();
			picked_up.emplace(b);
		} else {
			if (not picked_up.contains(b))
				fail();
			picked_up.erase(b);
		}
	}
	cout << (picked_up.empty() ? "yes\n" : "no\n");
}
