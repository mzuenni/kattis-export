// @EXPECTED_RESULTS@: TIMELIMIT
#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<cassert>
using namespace std;
const int MAX=1000000;
const int INF=2000000000;

int n,m,matched[MAX],dist[MAX];
vector<int> s[MAX];
bool b[MAX];
bool check(int x) {
  b[x]=true;
  for (int i=0; i<s[x].size(); i++) if (s[x][i]!=matched[x]
    && (!matched[s[x][i]] || dist[x]+1==dist[matched[s[x][i]]]
    && !b[matched[s[x][i]]] && check(matched[s[x][i]]))) {
    matched[x]=s[x][i];
    matched[s[x][i]]=x;
    return true;
  }
  return false;
}
int matching() {
  int i,j,k,ans=0;
  vector<int> q;  
  for (i=1; i<=n+m; i++) matched[i]=0;
  while (1) {
    q.clear();
    for (i=1; i<=n; i++) {
      if (!matched[i]) {
        q.push_back(i);
        dist[i]=0;
      } else
        dist[i]=INF;
      b[i]=false;
    }
    for (i=0; i<q.size(); i++) for (j=0; j<s[q[i]].size(); j++) {
      k=s[q[i]][j];
      if (!matched[k]) goto proceed;
      if (dist[q[i]]+1<dist[matched[k]]) {
        q.push_back(matched[k]);
        dist[matched[k]]=dist[q[i]]+1;
      }
    }      
    break;
proceed:
    for (i=1; i<=n; i++) ans+=!matched[i] && check(i);
  }
  return ans;
}

int T,M,N,x[MAX],y[MAX];
bool solve(){
	n=N;
	m=M;
	for(int i=1;i<=n;i++){
		s[i].clear();
		int from=x[i-1],to=y[i-1];
		while(1){
			s[i].push_back(n+from+1);
			if(from==to)break;
			++from;
			if(from==M)from=0;
		}
	}
	return matching()==n;
}
main(){
	scanf("%d",&T);
	assert(1<=T&&T<=100);
	while(T--){
		scanf("%d %d",&M,&N);
		assert(1<=M&&M<=1000000000);
		assert(1<=N&&N<=MAX);
		for(int i=0;i<N;i++){
			scanf("%d %d",&x[i],&y[i]);
			assert(0<=x[i]&&0<=y[i]&&x[i]<M&&y[i]<M);
		}
		puts(solve()?"YES":"NO");
	}
}

