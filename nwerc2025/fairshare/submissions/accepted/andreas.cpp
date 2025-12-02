#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	int receive = accumulate(a.begin(), a.end(), 0);
	int to_pay = accumulate(b.begin(), b.end(), 0);
	for (int i = 0; i < n; i++) {
		if (to_pay - receive + a[i] <= b[i]) {
			cout << i + 1 << '\n';
			return 0;
		}
	}
	cout << "impossible\n";
}