#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

#define int int64_t

template <typename Cmp>
using tree = __gnu_pbds::tree<int, __gnu_pbds::null_type,
	Cmp, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

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
		for (; k < n and t < max_t; t += r) {
			int max_stop = 0, wait = 0;
			tree<std::less<int>> stops;
			tree<std::less_equal<int>> mstops;
			while (k < n) {
				wait += stops.order_of_key(ds[k]) + 1;
				mstops.insert(ds[k]);
				if (stops.insert(ds[k]).second)
					wait += mstops.size() - mstops.order_of_key(ds[k] + 1);
				if (t + wait * 2 * w + ts[max(max_stop, ds[k])] > max_t)
					break;

				max_stop = max(max_stop, ds[k]);
				k++;
			}
			if (max_stop == 0) {
				return false;
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
