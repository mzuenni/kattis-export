#include <iostream>
#include <numeric>

using namespace std;

int pa[200200];
int ufind(int i) { return pa[i] == i ? i : pa[i] = ufind(pa[i]); }
int num[200200];

int main() {
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	iota(pa, pa+200200, 0);
	while (m-- > 0) {
		int i, j;
		cin >> i >> j;
		pa[ufind(i)] = ufind(j);
	}
	fill_n(num, n, 0);
	for (int i = 0; i <= n; i++)
		num[ufind(i)]++;
	int res = 0;
	for (int i = 0; i < n; i++)
		res = max(res, num[i]);
	cout << res << '\n';
}
