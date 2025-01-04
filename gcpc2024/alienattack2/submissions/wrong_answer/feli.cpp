#include<vector>
#include<iostream>
#include<cstring>

using namespace std;

vector<int> adj[200001];
int visited[200001];
int compsize[200001];

void dfs(int i, int c){
	if(visited[i]) return;
	visited[i] = c;
	for(int j = 0; j< adj[i].size(); j++){
		dfs(adj[i][j], c);
	}
	compsize[c]++;
	return;
}

int main(){
	int n, m;
	cin >> n >> m;
	for(int i = 0; i< m; i++){
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int comps = 0;
	
	
	memset(visited,0,  sizeof(visited));
	memset(compsize,0,  sizeof(compsize));

	for (int i = 0; i< n; i++){
		if(visited[i] == 0){
			comps++;
			dfs(i, comps);
			cerr << i << ", " << comps << ", " << compsize[comps] << endl;
		}
	}
	int maxcomp = 0;
	for(int i = 0; i< comps; i++){
		maxcomp = max(maxcomp, compsize[i]);
	}
	cout << maxcomp << endl;
}
