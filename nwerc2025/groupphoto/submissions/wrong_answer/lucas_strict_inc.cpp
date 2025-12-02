#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)
#define all(x) (x).begin(), (x).end()

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<pair<int, int>> b;
	for(int &e : a) cin >> e, e--;
	for(int i = 0; i < n; i++){
		if(a[i] >= i) b.emplace_back(2*i+1, 2*(a[i]-i));
		if(a[i] >= n-1-i) b.emplace_back(2*(a[i]-(n-1-i)), 2*(n-1-i)+1);
	}
	sort(all(b));
	vector<int> p;
	for(auto [x, y] : b){
		auto it = lower_bound(all(p), y);
		if(it == p.end()) p.push_back(y);
		else *it = y;
	}
	cout << n-sz(p) << "\n";
}