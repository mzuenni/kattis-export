#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n; ll t;
	cin >> n >> t;
	vector<ll> a(n);
	for(ll& x : a) cin >> x;
	for(int i = 0; i < n && t > 0; i += 2){
		if(a[i] > 0){
			t--;
			ll x = 1;
			for(int j = i; j < n; j++){
				a[j]++;
				x--;
				if(x == 0){
					if(a[j] == 1) break;
					x = a[j];
					a[j] = 0;
				}
			}
		}
		a[i] += t%2;
		if(i+1 < n) a[i+1] += t/2;
		t /= 2;
	}
	for(int i = 0; i < n; i++) cout << a[i] << " \n"[i==n-1];
}