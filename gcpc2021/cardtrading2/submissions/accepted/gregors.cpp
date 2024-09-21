#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;
using ld = long double;

int main()
{
	int n; cin >> n;
	vector<tuple<ld,ll,ll>> bids;
	ll qb = 0;
	for (int i = 0; i < n; ++i)
	{
		ld p; cin >> p;
		ll b,s; cin >> b >> s;
		bids.emplace_back(p,b,s);
		qb += b;
	}
	sort(bids.begin(),bids.end());
	ld turnover = 0;
	ld price = 0;
	ll qs = 0;
	for (auto &[p,b,s] : bids)
	{
		qs += s;
		ld t = min(qb,qs) * p;
		if (t > turnover)
		{
			turnover = t;
			price = p;
		}
		qb -= b;
	}
	if (turnover == 0) cout << "impossible" << endl;
	else cout << setprecision(2) << fixed << price << " " << turnover << endl;
}
