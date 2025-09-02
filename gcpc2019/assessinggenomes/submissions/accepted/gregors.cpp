#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int score(string &s)
{
	for (int i = 1; i < s.size(); ++i)
	{
		if (s.size() % i != 0) continue;
		bool valid = true;
		for (int j = 0; j < s.size() && valid; j += i)
			if (s.substr(j,i) != s.substr(0,i))
				valid = false;
		if (valid) return i;
	}
	return s.size();
}

vector<int> scoreN(int n)
{
	vector<int> v;
	for (int i = 0; i < n; ++i)
	{
		string s; cin >> s;
		v.push_back(score(s));
	}
	sort(v.begin(),v.end());
	return v;
}

int main()
{
	int n; cin >> n;
	vector<int> virus = scoreN(n);
	vector<int> antivirus = scoreN(n);
	int x = 0;
	for (int i = 0; i < n; ++i)
		x += (virus[i] - antivirus[i]) * (virus[i] - antivirus[i]);
	cout << x << endl;
}
