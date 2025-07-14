#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, d;
	cin >> n >> d;
	vector<vector<int>> a(n);
	for(int i = 0; i < n; i++){
		int p;
		cin >> p;
		a[p].push_back(i);
	}
	for(int t = 0; t < n; t++){
		a[t].push_back(1e9);
		int prv = -2*d, la = -2*d;
		bool impossible = false;
		for(int x : a[t]){
			if(x - prv > d){
				if(prv - la >= d) impossible = true;
				la = x;
			}
			prv = x;
		}
		if(!impossible){
			cout << t << "\n";
			break;
		}
	}
}