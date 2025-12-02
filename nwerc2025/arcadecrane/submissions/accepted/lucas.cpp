#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main(){
	cin.tie()->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int &e : a) cin >> e, e--;
	vector<pair<int, int>> ans;
	auto doOp = [&](int i, int j){
		if(i == j) return;
		ans.emplace_back(i+1, j+1);
		vector<int> v(a.begin()+i, a.begin()+i+3);
		a.erase(a.begin()+i, a.begin()+i+3);
		a.insert(a.begin()+j, all(v));
	};
	for(int k = n-1; k >= 5; k--){
		int p = 0;
		for(int i = 0; i < n; i++){
			if(a[i] == k) p = i;
		}
		if(p < 2) doOp(0, 2), k++;
		else doOp(p-2, k-2);
	}
	mt19937 rng(42);
	uniform_int_distribution<int> dis(0, 2);
	while(!is_sorted(all(a))){
		doOp(dis(rng), dis(rng));
	}
	cout << ans.size() << "\n";
	for(auto [i, j] : ans) cout << i << " " << j << "\n";
}