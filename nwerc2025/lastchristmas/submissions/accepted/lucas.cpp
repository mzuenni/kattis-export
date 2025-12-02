#include <bits/stdc++.h>
using namespace std;

constexpr int M = 10;

int main(){
	cin.tie(0)->sync_with_stdio(false);
	int n;
	cin >> n;
	map<string, vector<int>> mp;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < M; j++){
			string s;
			cin >> s;
			mp.emplace(s, vector<int>(M+1, 0));
			mp[s][0]++;
			mp[s][1+j]++;
		}
	}
	vector<string> names;
	vector<int> best;
	for(auto [s, v] : mp){
		if(best < v) best = v, names.clear();
		if(best == v) names.push_back(s);
	}
	if(names.size() > 1) cout << "tie\n";
	else cout << names[0] << "\n";
}