#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int main()
{
	int n,d,k;
	cin >> n >> d >> k;
	vector<pair<int, string>> employees;
	for (int i = 0; i < n; ++i)
	{
		string s;
		int c;
		cin >> s >> c;
		employees.push_back(make_pair(c,s));
	}
	sort(employees.begin(), employees.end(), greater<pair<int,string>>());
	int colleted = 0;
	int cnt = 0;
	for (pair<int,string> &e : employees)
	{
		colleted += e.first;
		cnt++;
		if (colleted >= d)
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