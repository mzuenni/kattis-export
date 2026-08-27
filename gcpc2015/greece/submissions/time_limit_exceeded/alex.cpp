#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef pair<int, ll> pil;

const int oo = 0x3f3f3f3f;
const ll loo = (((ll)oo)<<32)+oo;

#define all(c) (c).begin(), (c).end()
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

void calc(){
	int N, P, M, G, T, s, t, d;
	cin >> N >> P >> M >> G >> T;
	vector<int> places(P+1, 0);
	FOR(i,0,P){
		cin >> places[i] >> d;
		G -= d;
	}
	sort(all(places)); 
	vector<vector<pil > > adjl(N);
	while(M-->0){
		cin >> s >> t >> d;
		adjl[s].push_back(make_pair(t,d));
		adjl[t].push_back(make_pair(s,d));
	}
	P = places.size();
	// perform P dijkstras O(N^2*P)
	vector<vector<ll> > adjm(P,vector<ll>(P));
	FOR(sid,0,P){
		vector<ll> dist(N,loo);
		vector<bool> done(N,false);
		dist[places[sid]] = 0;
		while(true){
			int n = -1;
			FOR(i,0,N)if(!done[i])if(n==-1||dist[i]<dist[n])n = i;
			if(n == -1)break;
			if(dist[n] == loo)break;
			for(auto ed: adjl[n]){
				if(dist[ed.first] > dist[n]+ed.second)dist[ed.first]=dist[n]+ed.second;
			}
			done[n] = true;
		}
		FOR(tid,0,P)adjm[sid][tid] = dist[places[tid]];
	}
	// dp[position][mask] where position refers to current position and mask refers to visited positions and lowest bit refers to whether taxi is already used O(2^P*P^2)
	vector<vector<ll> >best(P, vector<ll>(1<<P,loo));
	FOR(i,1,P)best[i][1<<i]=adjm[0][i];
	FOR(i,1,P)best[i][1|(1<<i)]=T;
	FOR(mask,0,1<<P)FOR(n,1,P){
		FOR(to,1,P){
			if(mask & (1<<to))continue;
			int omask = mask|(1<<to);
			best[to][omask] = min(best[to][omask], best[n][mask] + adjm[n][to]);
			if(mask & 1)continue;
			omask |= 1;
			best[to][omask] = min(best[to][omask], best[n][mask] + T);
		}
	}
	ll res = loo;
	FOR(i,1,P)res = min(res, best[i][(1<<P)-2] + adjm[i][0]);
	if(res <= G){
		cout << "possible without taxi\n";
		return;
	}
	FOR(i,1,P)res = min(res, best[i][(1<<P)-1] + adjm[i][0]);
	FOR(i,1,P)res = min(res, best[i][(1<<P)-2] + T);
	if(res <= G){
		cout << "possible with taxi\n";
	} else {
		cout << "impossible\n";
	}
}
int main() {
	calc();
	return 0;
}
