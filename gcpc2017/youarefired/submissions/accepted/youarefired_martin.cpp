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
using namespace std;
#define db(a) (cout << (#a) << " = " << (a) << endl)
typedef long long ll;

ll N,D,K;

vector<pair<ll, string>> emps;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>N>>D>>K;
	for(ll i=0;i<N;i++) 
	{
		string s;
		ll c;
		cin>>s>>c;
		emps.push_back({c, s});
	}
	sort(emps.begin(), emps.end(), greater<pair<ll, string>>());
	size_t i = 0;
	for(;i<emps.size() && i<size_t(K);++i)
	{
		D -= emps[i].first;
		if(D <= 0) break;
	}
	if(D > 0) cout << "impossible\n";
	else 
	{
		cout << i+1 << "\n";
		for(size_t j=0;j<=i;++j) cout << emps[j].second << ", YOU ARE FIRED!\n";
	}
	return 0;
}

