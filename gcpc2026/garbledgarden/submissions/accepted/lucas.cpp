#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)
#define all(x) (x).begin(), (x).end()

vector<vector<pair<int, int>>> g;
vector<int> tour;

void dfs(int u){
	while(!g[u].empty()){
		auto [v, i] = g[u].back();
		g[u].pop_back();
		dfs(v);
		tour.push_back(i);
	}
}

int main(){
int n;
	cin >> n;
	g.resize(n);
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i], a[i]--;
	vector<int> b = a;
	sort(all(b));
	int start = -1, cnt = 0;
	for(int i = 0; i < n; i++){
		if(a[i] != b[i]){
			g[a[i]].emplace_back(b[i], i);
			start = a[i];
			cnt++;
		}
	}
	if(cnt == 0) cout << "0\n";
	else{
		dfs(start);
		reverse(all(tour));
		if(sz(tour) == cnt){
			cout << "1\n";
			cout << sz(tour);
			for(int i : tour) cout << " " << i+1;
			cout << "\n";
		}
		else{
			vector<int> p(n), inv(n);
			iota(all(p), 0);
			sort(all(p), [&](int i, int j){return a[i] < a[j];});
			for(int i = 0; i < n; i++) inv[p[i]] = i;
			vector<bool> vis(n);
			vector<int> op1, op2;
			for(int i = 0; i < n; i++){
				if(vis[i]) continue;
				op2.push_back(inv[i]);
				int c = i;
				while(!vis[c]){
					vis[c] = true;
					op1.push_back(c);
					c = p[c];
				}
			}
			reverse(all(op2));
			cout << "2\n";
			cout << sz(op1);
			for(int i : op1) cout << " " << i+1;
			cout << "\n" << sz(op2);
			for(int i : op2) cout << " " << i+1;
			cout << "\n";
		}
	}
}