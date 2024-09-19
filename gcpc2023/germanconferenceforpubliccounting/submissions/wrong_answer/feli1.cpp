#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
	ll n;
	cin >> n;
	int signs = 0;
	for(int i = 1; i< 10; i++){
		ll num = i;
		while(num <= n){
			num= num*10+i;
			signs++;
		}
	}
	signs++;
	ll num = 1;
	while(num <= n){
		num=num*10;
		signs++;
	}
	cout << signs << endl;
}
