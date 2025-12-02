#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
	auto test = [&](int i){
		int pay = 0, has = 0;
		for(int j = 0; j < n; j++){
			pay += b[j];
			if(j != i) has += a[j];
		}
		return pay - has <= b[i];
	};
	vector<int> ord(n);
	iota(all(ord), 0);
	sort(all(ord), [&](int i, int j){return b[i] > b[j];});
	for(int i = 0; i < min(n, 1000); i++){
		if(test(ord[i])){
			cout << ord[i]+1 << "\n";
			return 0;
		}
	}
	cout << "impossible\n";
}