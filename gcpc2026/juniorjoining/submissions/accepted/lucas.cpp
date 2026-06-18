#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()
#define sz(x) int(size(x))

constexpr int C = 1e6 + 1;

vector<int> byC[C];

int main(){
	int n;
	cin >> n;
	ll add = 0;
	vector<ll> a(2*n);
	for(int i = 0; i < 2*n; i++){
		int l, r, c;
		cin >> l >> r >> c;
		add += l;
		a[i] = r-l;
		byC[c].push_back(i);
	}
	vector<ll> b;
	for(int c = 0; c < C; c++){
		vector<int> v = byC[c];
		sort(all(v), [&](int i, int j){return a[i] > a[j];});
		for(int i = 0; i < sz(v); i++){
			b.push_back(a[v[i]] + c*(min(i+1, sz(v)-i-1) - min(i, sz(v)-i)));
		}
	}
	sort(b.rbegin(), b.rend());
	cout << add + accumulate(b.begin(), b.begin()+n, 0ll) << "\n";
}