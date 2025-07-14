#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n; ll t;
	cin >> n >> t;
	vector<ll> a(n);
	for(ll& e : a) cin >> e;
	for(ll i = 0; i < t; i++){
		ll x = 1; // number of stones in Bill's hand
		for(int j = 0; j < n; j++){ // j = position of Bill's hand
			a[j]++;
			x--;
			if(x == 0){
				if(a[j] == 1) break;
				x = a[j];
				a[j] = 0;
			}
		}
	}
	for(ll x : a) cout << x << " ";
	cout << "\n";
}