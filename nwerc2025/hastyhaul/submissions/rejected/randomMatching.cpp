// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <bits/stdc++.h>
using namespace std;
#define all(x) ::begin(x), ::end(x)
#define sz(x) (int)::size(x)
using ll = long long;
using ull = unsigned long long;

vector<vector<ll>> nck;

int od(int n, int k){
	return nck[n][k] & 1;
}

map<pair<int, int>, map<ull, ull>> matchings;

pair<int, int> solve(vector<int> a){
	int n = sz(a);
	int k = (int)count(all(a), 1);
	if(od(n, k)) return {-1, -1};
	if(nck[n][k] < 2e5){
		if(!matchings.contains({n, k})){
			map<ull, ull> matching;
			vector<int> cur(n-k, 0);
			for(int i = 0; i < k; i++) cur.push_back(1);
			mt19937 rng(42);
			do{
				ull u = 0;
				for(int i = 0; i < n; i++){
					if(cur[i]) u |= 1ull << i;
				}
				if(matching.contains(u)) continue;
				while(true){
					ull w;
					int cnt = 0;
					for(int i = 0; i < n; i++){
						if(1 & (u >> i)){
							for(int j = 0; j < n; j++){
								if(!(1 & (u >> j))){
									ull v = u;
									v ^= 1ull << i;
									v ^= 1ull << j;
									if(!matching.contains(v)){
										matching[u] = v;
										matching[v] = u;
										goto done;
									}
									if(uniform_real_distribution<double>(0, 1)(rng) <= 1.0 / ++cnt) w = v;
								}
							}
						}
					}
					ull v = matching[w];
					matching.erase(v);
					matching[u] = w;
					matching[w] = u;
					u = v;
				}
				done:;
			}while(next_permutation(all(cur)));
			matchings[{n, k}] = matching;
		}
		ull u = 0;
		for(int i = 0; i < n; i++){
			if(a[i]) u |= 1ull << i;
		}
		ull v = matchings[{n, k}][u];
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(a[i] == 1 && a[j] == 0 && !(1 & (v >> i)) && (1 & (v >> j))) return {i, j};
			}
		}
	}
	else{
		mt19937 rng(42);
		vector<bool> vis(n);
		int rem = n-1;
		for(int i = 0; i < n; i++){
			if(vis[i]) continue;
			vis[i] = true;
			assert(rem>0);
			int v = uniform_int_distribution<int>(0, rem-1)(rng);
			int j = 0;
			while(vis[j] || v > 0){
				if(!vis[j]) v--;
				j++;
			}
			vis[j] = true;
			rem -= 2;
			if(a[i] != a[j]){
				if(a[i]) return {i, j};
				else return {j, i};
			}
		}
	}
	assert(false);
}

int main() {
	cin.tie(0)->sync_with_stdio(false);
	cout << setprecision(16);
	constexpr int N = 65;
	nck.assign(N, vector<ll>(N));
	for(int i = 0; i < N; i++){
		nck[i][0] = 1;
		for(int j = 1; j <= i; j++){
			nck[i][j] = nck[i-1][j] + nck[i-1][j-1];
		}
	}
	int t;
	cin >> t;
	while(t--){
		int n, m, k;
		cin >> n >> m >> k;
		vector<int> a;
		for(int i = 0; i < n; i++){
			string s;
			cin >> s;
			for(char c : s) a.push_back(c == '#');
		}
		auto [i, j] = solve(a);
		if(i == -1) cout << "risky\n";
		else{
			if(a[i] == 0) swap(i, j);
			cout << (i/m)+1 << " " << (i%m)+1 << "\n";
			cout << (j/m)+1 << " " << (j%m)+1 << "\n";
		}
	}
}
