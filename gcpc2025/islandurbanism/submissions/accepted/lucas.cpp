#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)size(x)
constexpr ll inf = 1e18;

int main(){
	int n, m, numVil, numTer;
	cin >> n >> m >> numVil >> numTer;
	vector<int> vilSz(numVil), isTer(n), terInVil(numVil);
	for(int &e : vilSz) cin >> e;
	vector<vector<pair<int, ll>>> g(n);
	for(int i = 0; i < m; i++){
		int u, v; ll len;
		cin >> u >> v >> len;
		u--, v--;
		g[u].emplace_back(v, len);
		g[v].emplace_back(u, len);
	}
	for(int i = 0; i < numTer; i++){
		int t;
		cin >> t;
		isTer[--t]++;
	}
	int l = 0;
	vector<ll> toBoth(numVil), toLeft(numVil), toRight(numVil), split(numVil);
	ll ans = inf;
	int cntWith = 0, vilWith = -1;
	vector<ll> vilEdge(numVil);
	for(int vil = 0; vil < numVil; vil++){
		int r = l + vilSz[vil];
		for(auto [v, len] : g[r-1]){
			if(v == r%n) vilEdge[vil] = len;
		}
		vector<int> ter = {l, r-1};
		for(int i = l; i < r; i++) if(isTer[i]) ter.push_back(i);
		if(sz(ter) > 2) cntWith++, vilWith = vil;
		terInVil[vil] = sz(ter)-2;
		vector<vector<ll>> dp(1 << sz(ter), vector<ll>(r-l, inf));
		dp[0] = vector<ll>(r-l, 0);
		for(int msk = 1; msk < (1<<sz(ter)); msk++){
			for(int u = l; u < r; u++){
				for(int i = 0; i < sz(ter); i++){
					if(1 & (msk >> i)){
						if(ter[i] == u) dp[msk][u-l] = dp[msk ^ (1<<i)][u-l];
					}
				}
				for(int sub = (msk-1)&msk; sub; sub = (sub-1)&msk){
					dp[msk][u-l] = min(dp[msk][u-l], dp[sub][u-l] + dp[msk^sub][u-l]);
				}
			}
			priority_queue<pair<ll, int>> pq;
			for(int u = l; u < r; u++) pq.emplace(-dp[msk][u-l], u);
			while(!pq.empty()){
				auto [d, u] = pq.top(); pq.pop();
				d = -d;
				if(d > dp[msk][u-l]) continue;
				for(auto [v, len] : g[u]){
					if(v < l || v >= r || d+len >= dp[msk][v-l]) continue;
					dp[msk][v-l] = d+len;
					pq.emplace(-(d+len), v);
				}
			}
		}
		int msk = (1<<sz(ter))-1;
		toBoth[vil] = dp[msk][ter[0]-l];
		toLeft[vil] = dp[msk-2][ter[0]-l];
		toRight[vil] = dp[msk-1][ter[1]-l];
		if(sz(ter) > 2) ans = dp[msk-3][ter[2]-l];
		int mskSmall = msk >> 2;
		split[vil] = min(toLeft[vil], toRight[vil]);
		for(int sub = (mskSmall-1) & mskSmall; sub; sub = (sub-1) & mskSmall){
			split[vil] = min(split[vil], dp[1 | (sub<<2)][ter[0]-l] + dp[2 | ((mskSmall^sub)<<2)][ter[1]-l]);
		}
		l += vilSz[vil];
	}
	ll fullCircle = 0;
	for(int vil = 0; vil < numVil; vil++) fullCircle += toBoth[vil] + vilEdge[vil];
	if(cntWith == 1){
		ans = min(ans, fullCircle - toBoth[vilWith] + split[vilWith]);
		cout << ans << "\n";
		return 0;
	}
	ans = inf;
	for(int vil = 0; vil < numVil; vil++){
		ans = min(ans, fullCircle - toBoth[vil] + split[vil]);
		ll splEdge = fullCircle - vilEdge[vil];
		for(int i = (vil+1)%numVil;; i = (i+1)%numVil){
			if(terInVil[i] == 0) splEdge -= toBoth[i] + vilEdge[i];
			else{
				splEdge += toRight[i] - toBoth[i];
				break;
			}
		}
		for(int i = vil;; i = (i-1+numVil)%numVil){
			if(terInVil[i] == 0) splEdge -= toBoth[i] + vilEdge[(i-1+numVil)%numVil];
			else{
				splEdge += toLeft[i] - toBoth[i];
				break;
			}
		}
		ans = min(ans, splEdge);
	}
	cout << ans << "\n";
}