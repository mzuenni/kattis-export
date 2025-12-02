#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	if(n % 2 == 1) cout << n/2 << "\n";
	else cout << 2*(n/4)-1 << "\n";
}