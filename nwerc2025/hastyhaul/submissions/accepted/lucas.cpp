#include <bits/stdc++.h>
using namespace std;
#define all(x) ::begin(x), ::end(x)
#define sz(x) (int)::size(x)

int od(int n, int k){
	return (n & k) == k;
}

pair<int, int> solve(vector<int> a){
	int n = sz(a);
	int k = (int)count(all(a), 1);
	if(od(n, k)) return {-1, -1};
	vector<int> p(n);
	iota(all(p), 0);
	for(int i = 0; i < sz(a); n--, k -= a[p[i++]]){
		if(!od(n, k) && od(n-1, k-a[p[i]])){
			bool ok = a[p[i]] || a[p[i+k]];
			for(int j = 1; j < k; j++){
				if(a[p[i+j]] == 0) ok = false;
			}
			if(ok) return {p[i], p[i+k]};
		}
		else if(od(n, k) && od(n-1, k)) swap(p[i], p[i+k]);
	}
	assert(false);
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	cout << setprecision(16);
	int t;
	cin >> t;
	while(t--){
		int n, m, k;
		cin >> n >> m >> k;
		vector<int> a;
		for(int i = 0; i < n; i++){
			string s;
			cin >> s;
			for(char c : s) a.push_back(c == '#');
		}
		auto [i, j] = solve(a);
		if(i == -1) cout << "risky\n";
		else{
			if(a[i] == 0) swap(i, j);
			cout << (i/m)+1 << " " << (i%m)+1 << "\n";
			cout << (j/m)+1 << " " << (j%m)+1 << "\n";
		}
	}
}
