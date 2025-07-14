// @EXPECTED_RESULTS@: Accepted, Time_Limit_Exceeded
// Not sure what the runtime of this actually is O(n * log(n)), O(n * sqrt(n) * log(n)), O(n^2), or something else?
// Likely not a priority as it is unlikely teams will attempt so solve it this way.
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int main(){
	int n, d;
	cin >> n >> d;
	vector<vector<int>> a(n);
	for(int i = 0; i < n; i++){
		int p;
		cin >> p;
		a[p].push_back(i);
	}
	vector<int> vis(n, -1);
	for(int t = 0; t < n; t++){
		if(a[t].empty()){
			cout << t << "\n";
			break;
		}
		auto isEmpty = [&](int l, int r){
			return lower_bound(all(a[t]), l) == lower_bound(all(a[t]), r);
		};
		auto isOk = [&](int i){
			return isEmpty(i+d, i+2*d);
		};
		auto rec = [&](auto&& self, int i) -> bool {
			if(i >= a[t].back()) return true;
			if(vis[i] == t) return false;
			vis[i] = t;
			if(!isEmpty(i, i+2*d) && isOk(i) && self(self, i+2*d)) return true;
			auto it = lower_bound(all(a[t]), i+d);
			while(it != a[t].end() && isEmpty(i, *it-d+1)){
				if(isOk(*it-d+1) && self(self, *it-d+1)) return true;
				it++;
			}
			return false;
		};
		if(rec(rec, 0)){
			cout << t << "\n";
			break;
		}
	}
}
