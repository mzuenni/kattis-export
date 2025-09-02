#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <climits>
#include <cstdio>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <functional>
#include <numeric>
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

size_t N;
vector<pair<int, int>> A;

int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b, a%b);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
	cin>>N;
	for(size_t i=0;i<N;i++) 
	{
		int x, y;
		cin>>x>>y;
		A.push_back({x, y});
	}
	ll b = gcd(abs(A[0].first - A[A.size()-1].first), abs(A[0].second - A[A.size()-1].second));
	for(size_t i=1;i<A.size();i++)
	{
		b += gcd(abs(A[i].first-A[i-1].first), abs(A[i].second-A[i-1].second));
	}
	ll dA = A[A.size()-1].first * A[0].second - A[0].first * A[A.size()-1].second;
	for(size_t i=0;i+1<A.size();i++)
	{
		dA += A[i].first * A[i+1].second;
		dA -= A[i+1].first * A[i].second;
	}
	dA = abs(dA);
	ll i = (dA - b + 2) / 2;
	cout << i << "\n";
  return 0;
}

