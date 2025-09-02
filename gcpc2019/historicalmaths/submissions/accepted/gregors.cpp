#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

vector<ll> readNumber()
{
	int n; cin >> n;
	vector<ll> num(n);
	for (int i = n-1; i >= 0; --i)
	{
		cin >> num[i];
	}
	return num;
}

vector<ll> mult(vector<ll> &a, vector<ll> &b, ll base)
{
	vector<ll> c(a.size()+b.size(),0);
	for (int i = 0; i < a.size();  ++i)
	{
		for (int j = 0; j < b.size(); ++j)
		{
			c[i+j] += a[i] * b[j];
			c[i+j+1] += c[i+j] / base;
			c[i+j] %= base;
		}
	}
	return c;
}

bool lessvector(vector<ll> &a, vector<ll> &b)
{
	for (int i = a.size()-1; i >= 0; --i)
		if (a[i] != b[i])
			return a[i] < b[i];
	return false;
}

int main()
{
	vector<ll> a = readNumber();
	vector<ll> b = readNumber();
	vector<ll> c = readNumber();
	while (c.size() < a.size() + b.size())
		c.push_back(0);
	ll lower = *max_element(a.begin(),a.end());
	lower = max(lower, *max_element(b.begin(),b.end()));
	lower = 1 + max(lower, *max_element(c.begin(),c.end()));
	ll upper = (1LL << 61);
	while (lower <= upper)
	{
		ll mid = (lower + upper) / 2;
		vector<ll> res = mult(a,b,mid);
		if (res == c)
		{
			cout << mid << endl;
			return 0;
		}
		if (lessvector(res,c))
			upper = mid - 1;
		else
			lower = mid + 1;
	}
	cout << "impossible" << endl;
}

