#include <iostream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

int main()
{
	int n, s1, s2; cin >> n >> s1 >> s2;
	map<int,int> crates;
	vector<int> loc(n+1);
	int res = 0;
	for (int i = 0; i <= n; ++i)
	{
		int x; cin >> x;
		loc[x] = i < s1 ? i : n-i+s1;
		crates[loc[x]] = x;
		if ((i == s1-1 || i == n) && x == 0) res++;
	}
	for (int i = 1; i <= n; ++i)
	{
		auto it = crates.find(loc[i]);
		res += next(it) != crates.end() && next(it)->second == 0;
		res += it != crates.begin() && prev(it)->second == 0;
		crates.erase(it);
	}
	cout << res << endl;
}
