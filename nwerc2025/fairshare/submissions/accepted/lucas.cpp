#include <bits/stdc++.h>
using namespace std;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	int x = 1e9, y = 0, ind = -1;
	for(int i = 0; i < n; i++){
		int a, b;
		cin >> a >> b;
		a -= b;
		if(a < x) x = a, ind = i+1;
		y += a;
	}
	if(x <= y) cout << ind << "\n";
	else cout << "impossible\n";
}