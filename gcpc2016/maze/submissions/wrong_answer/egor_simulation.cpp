#include <bits/stdc++.h>
using namespace std;

//use random walk, remember how many runs have been successful
int MAX_CNT=1000000;


int main() {
    std::srand(std::time(0));
	int n, m; cin >> n >> m;
	vector<std::vector<vector<size_t> > > graph(n,std::vector<vector<size_t> >(26));
	for(size_t i=0;i<m;i++) {
		size_t a, b; char c;
		cin >> a >> b >> c;
		a--, b--;
		graph[a][c-'A'].push_back(b);
		graph[b][c-'A'].push_back(a);
	}
	string s; cin >> s;
	int found=0;
	for(int i=0;i<MAX_CNT;i++){
	  size_t cur=0;
	  for(size_t ch=0;ch<s.size();ch++){
	    std::vector<size_t> &possible=graph[cur][s[ch]-'A'];
	    size_t poss_cnt=possible.size();
	    if(poss_cnt==0)
	        continue;
	    size_t next_door=std::rand()%poss_cnt;
	    cur=possible[next_door];
	    if(cur==n-1){
	        found++;
	        break;
	    }       
	  }
	}
	
	cout << (100.0*found/MAX_CNT)<<endl;
}
