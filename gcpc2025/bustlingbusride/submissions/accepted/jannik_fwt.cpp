#include <iostream>
#include <vector>

using namespace std;

#define int int64_t
#define sz(a) ((int)(a).size())

struct fwt_t {
	vector<int> bi_tree;
	void clear(int n)
	{
		bi_tree.assign(n, 0);
	}
	fwt_t(int n = 0)
	{
		clear(n);
	}
	void add(int pos, int val)
	{
		if (pos == 0) {
			bi_tree[0] += val;
			return;
		}
		while (pos < sz(bi_tree)) {
			bi_tree[pos] += val;
			pos += pos & (-pos);
		}
	}
	int rank(int pos)
	{
		if (pos < 0)
			return 0;
		int res = bi_tree[0];
		for (; pos != 0; pos &= pos - 1)
			res += bi_tree[pos];
		return res;
	}
};

signed main()
{
	int n, b, r, w;
	cin >> n >> b >> r >> w;
	vector<int> ts(b + 1);
	for (int i = 1; i <= b; i++) {
		cin >> ts[i];
		ts[i] += ts[i - 1];
	}

	vector<int> ds(n);
	for (int& x : ds)
		cin >> x;
	const auto test = [&](int max_t) -> bool {
		int k = 0, t = 0;
		fwt_t stops(b + 1), people(b + 1);
		for (; k < n and t < max_t; t += r) {
			int max_stop = 0, wait = 0;
			const int start = k;
			while (k < n) {
				wait += stops.rank(ds[k] - 1) + 1;
				people.add(ds[k], 1);
				if (stops.rank(ds[k]) == stops.rank(ds[k] - 1)) {
					wait += k + 1 - start - people.rank(ds[k]);
					stops.add(ds[k], 1);
				}
				max_stop = max(max_stop, ds[k]);
				if (t + wait * 2 * w + ts[max_stop] > max_t)
					break;
				k++;
			}
			if (start == k)
				return false;
			for (int i = start; i <= min(n - 1, k); i++) {
				people.add(ds[i], -1);
				if (stops.rank(ds[i]) > stops.rank(ds[i] - 1))
					stops.add(ds[i], -1);
			}
		}
		return k == n;
	};
	int lo = 0, hi = 1;
	while (not test(hi))
		lo = hi, hi = 2 * hi;
	while (lo + 1 < hi) {
		int m = lo + (hi - lo) / 2;
		(test(m) ? hi : lo) = m;
	}
	cout << hi << endl;
}
