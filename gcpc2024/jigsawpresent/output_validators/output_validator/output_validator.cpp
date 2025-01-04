#include "validation.h"
typedef long long ll;
using namespace std;

int main(int argc, char *argv[]) {
	ifstream in(argv[1]);
	OutputValidator v(4, argv);
	ifstream res(argv[2]);

	int n; in >> n;
	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++)
		in >> a[i].first >> a[i].second;

	string possible = v.test_strings({"yes", "no"}, "possible");
	v.newline();

	string jury_answer;
	res >> jury_answer;

	if (possible == "no") {
		int k1 = v.read_integer("k1", 1, n);
		v.space();
		vector<ll> p1 = v.read_integers("p1", k1, 1, n);

		int k2 = v.read_integer("k2", 1, n);
		v.space();
		vector<ll> p2 = v.read_integers("p2", k2, 1, n);

		ll x = 0, y = 0;
		for (int i: p1) {
			x += a[i - 1].first;
			y += a[i - 1].second;
		}
		for (int i: p2) {
			x -= a[i - 1].first;
			y -= a[i - 1].second;
		}

		if (x != 0 || y != 0)
			v.WA("sums are not equal");

		auto check = [&](vector<ll>& p) {
			sort(p.begin(), p.end());
			int lst = -1;
			for (int i: p) {
				if (lst != -1 && lst == i)
					v.WA("output contains duplicate elements");
				lst = i;
			}
		};
		check(p1);
		check(p2);

		if (k1 == k2) {
			bool equal = true;
			for (int i = 0; i < k1; i++)
				equal &= p1[i] == p2[i];
			if (equal)
				v.WA("sets are identical");
		}
	} else {
		if (jury_answer == "no")
			v.WA("jury found a solution");
	}
}
