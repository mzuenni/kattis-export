#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

using i64 = int64_t;

void go(i64* a, i64 n, i64 t)
{
	if (t > 0 and a[0]) {
		// simulate
		i64 h = 1;
		for (i64 i = 0; i < n; i++) {
			a[i]++, h--;
			if (h > 0) continue;
			if (a[i] == 1) break;
			swap(a[i], h);
		}
		t--;
	}
	if (t == 0) return;
	assert(a[0] == 0);
	a[0] = t % 2;
	if (n == 1) return;
	a[1] += t / 2;
	if (n > 2)
		go(a + 2, n - 2, t / 2);
}

int main()
{
	i64 n, t;
	cin >> n >> t;
	vector<i64> a(n);
	for (auto& x : a)
		cin >> x;
	go(&a[0], n, t);
	for (auto x : a)
		cout << x << ' ';
	cout << '\n';
}
