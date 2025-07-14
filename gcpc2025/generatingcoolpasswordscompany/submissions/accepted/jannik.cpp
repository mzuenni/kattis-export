#include <iostream>

using namespace std;

int main()
{
	int n;
	cin >> n;
	constexpr int d = 126 - 33;
	for (int i = 0; i < n; i++) {
		string pw = "!!!!aA0!!!";
		fill_n(&pw[0], 3, (char)(33 + i % d));
		fill_n(&pw[7], 3, (char)(33 + i / d));
		cout << pw << '\n';
	}
}
