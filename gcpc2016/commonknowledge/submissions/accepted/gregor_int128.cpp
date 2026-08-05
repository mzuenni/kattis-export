#include <iostream>

typedef __int128_t ll;
#define FOR(i,a,b) for(int i = (a); i < (b); i++)

using namespace std;

void out(ll x){
	if (x){
		out(x / 10);
		cout << int(x % 10);
	}
}


int main(){
	int n; cin >> n;
	ll x = 1;
	FOR(i,0,n) x *= 8;
	out(x);
}
