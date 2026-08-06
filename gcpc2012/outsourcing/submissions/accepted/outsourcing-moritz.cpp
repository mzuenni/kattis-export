// @EXPECTED_RESULTS@: CORRECT
#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#include <queue>
#include <tr1/unordered_set>

using namespace std;

typedef pair<int,int> pii;
bool visited[1000], reaches[2][1000];
int gcount[2][1000], assembly_st[2], transfer_st[2], assembly_op[2], rcount[2][1000], rgraph[2][1000][1000], cases;
pii graph[2][1000][1000];

std::tr1::unordered_set< int > compared;

struct Compare{
	int op, to;
	bool reach;
	Compare( int op, int to, bool reach ) : op( op ), to( to ), reach( reach ) {}
};

bool part( const Compare & comp ){ return comp.reach; }

bool checksout( queue<pii> & que, const pii & p ){
	int pv[2];
	pv[0] = p.first;
	pv[1] = p.second;
	vector< Compare > comp[2];
	std::vector< Compare >::iterator itrs[2];
	for( int i = 0; i < 2; ++i ){
		sort( graph[i][pv[i]], graph[i][pv[i]] + gcount[i][pv[i]] );
		for( int c = 0; c < gcount[i][pv[i]]; ++c ){
			comp[i].push_back( Compare( graph[i][pv[i]][c].first, graph[i][pv[i]][c].second, reaches[i][graph[i][pv[i]][c].second] ) );
		}
		itrs[i] = stable_partition( comp[i].begin(), comp[i].end(), part );
	}

	if( itrs[0]-comp[0].begin() != itrs[1]-comp[1].begin() ) return false;

	for( int i = 0; i < itrs[0]-comp[0].begin(); ++i ){
		if( (comp[0][i].op != comp[1][i].op) || (comp[0][i].to == transfer_st[0]-1 && comp[1][i].to != transfer_st[1]-1) || (comp[1][i].to == transfer_st[1]-1 && comp[0][i].to != transfer_st[0]-1) )
			return false;
		pii item = pii( comp[0][i].to, comp[1][i].to );
		if( compared.find( (item.first << 16 | item.second ) ) == compared.end() ){
			que.push( item );
			compared.insert( item.first << 16 | item.second );
		}
	}
	return true;
}

void bfs( int id, int src ){
	queue<int> que;
	que.push( src );
	memset( visited, false, sizeof( bool ) * (src+1) );
	visited[src] = true;
	while( !que.empty() ){
		int front = que.front();
		reaches[id][front] = true;
		que.pop();
		for( int i = 0; i < rcount[id][front]; ++i ){
			if( !visited[rgraph[id][front][i]] ){
				visited[rgraph[id][front][i]] = true;
				que.push( rgraph[id][front][i] );
			}
		}
	}
}

int main(){
	cin >> cases;
	while( cases-- ){
		cin >> assembly_st[0] >> transfer_st[0] >> assembly_op[0] >> assembly_st[1] >> transfer_st[1] >> assembly_op[1];
		for( int i = 0; i < 2; ++i ){
			memset( gcount[i], 0, transfer_st[i] * sizeof(int) );
			memset( rcount[i], 0, transfer_st[i] * sizeof(int) );
			memset( reaches[i], false, transfer_st[i] * sizeof(bool) );
			for( int st = 0; st < assembly_st[i]; ++st ){
				int from, by, to;
				cin >> from >> to >> by;
				graph[i][from][gcount[i][from]] = make_pair( by, to );
				rgraph[i][to][rcount[i][to]] = from;
				++gcount[i][from];
				++rcount[i][to];
			}
			memset( visited, false, sizeof( bool ) * transfer_st[0] );
			bfs( i, transfer_st[i]-1 );
		}
		compared.clear();
		compared.insert( 0 );
		queue<pii> que;
		que.push( pii(0,0) );
		bool result = true;
		while( !que.empty() ){
			pii top = que.front();
			que.pop();
			if( !checksout( que, top ) ){
				result = false;
				break;
			}
		}
		cout << (result ? "eligible\n" : "not eligible\n");
	}
}
