#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef long long ll;

int main()
{
	int n, k;
	ll d;
	cin >> n >> d >> k;
	vector<pair<ll, string>> employees;
	for (int i = 0; i < n; ++i)
	{
		string s;
		ll c;
		cin >> s >> c;
		employees.push_back(make_pair(c,s));
	}
	sort(employees.begin(), employees.end(), greater<pair<ll,string>>());
	ll colleted = 0;
	int cnt = 0;
	for (pair<ll,string> &e : employees)
	{
		colleted += e.first;
		cnt++;
		// ERROR: should be >= d
		if (colleted > d)
			break;
	}
	if ((colleted < d) || (cnt > k))
		cout << "impossible" << endl;
	else
	{
		cout << cnt << endl;
		for (int i = 0; i < cnt; ++i)
			cout << employees[i].second << ", YOU ARE FIRED!" << endl;
	}
}