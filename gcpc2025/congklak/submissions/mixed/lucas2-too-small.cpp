// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n; ll t;
	cin >> n >> t;
	vector<ll> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	while(t > 0){
		if(a[0] != 0){
			ll x = 1;
			for(int j = 0; j < n; j++){
				a[j]++;
				x--;
				if(x == 0){
					if(a[j] == 1) break;
					x = a[j];
					a[j] = 0;
				}
			}
			t--;
		}
		else{
			int k = 0;
			while((1ll<<(k+1)) <= t && a[2*(k+1)] == 0) k++; 
			for(int i = 0; i < k; i++) a[2*i+1] += 1ll<<(k-1-i);
			a[2*k]++;
			t -= 1ll<<k;
		}
	}
	for(int i = 0; i < n; i++) cout << a[i] << " ";
	cout << "\n";
}