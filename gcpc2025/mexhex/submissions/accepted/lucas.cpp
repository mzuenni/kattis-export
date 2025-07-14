#include <bits/stdc++.h>
#define sz(x) (int)size(x)
using namespace std;

int main(){
	int n, d;
	cin >> n >> d;
	vector<vector<int>> v(n+1);
	for(int i = 0; i < n; i++){
		int p;
		cin >> p;
		v[p].push_back(i);
	}
	int ans = 0;
	for(auto a : v){
		a.push_back(1e9);
		int s = 0, l = 0;
		bool ok = true;
		for(int i = 1; i < sz(a); i++){
			if(a[i] - a[i-1] >= d){
				if(a[i-1] - a[l] >= d) ok = false;
				s = max(s, a[i-1]-d+1) + 2*d;
				if(s > a[i]) ok = false;
				l = i;
			}
		}
		if(ok){
			cout << ans << "\n";
			return 0;
		}
		ans++;
	}
}