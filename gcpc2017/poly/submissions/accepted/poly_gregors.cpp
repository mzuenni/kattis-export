#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;
typedef long long LL;

LL gcd(LL a, LL b)
{
	while (a > 0)
	{
		b %= a;
		swap(a,b);
	}
	return b;
}

LL polyAreaTwo(vector<pair<LL,LL>> &p)
{
	LL area = 0;
	for (int i = 0; i < p.size(); ++i)
	{
		int j = (i+1) % p.size();
		area += p[i].first * p[j].second;
		area -= p[j].first * p[i].second;
	}
	return abs(area);
}

LL borderPoints(vector<pair<LL,LL>> &p)
{
	LL b = 0;
	for (int i = 0; i < p.size(); ++i)
	{
		int j = (i+1) % p.size();
		b += gcd(abs(p[i].first - p[j].first), abs(p[i].second - p[j].second));
	}
	return b;
}

int main()
{
	int n;
	cin >> n;
	vector<pair<LL,LL>> points(n);
	for (int i = 0; i < n; ++i)
		cin >> points[i].first >> points[i].second;
	cout << (polyAreaTwo(points) + 2 - borderPoints(points)) / 2 << endl;
}
