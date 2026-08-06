// @EXPECTED_RESULTS@: WRONG-ANSWER
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
#include <limits>
#include <utility>

using namespace std;

#define MAXN 10000
#define MAXD 10
#define MAXT 8

int treasures[MAXT], table[MAXT+1][MAXT+1], distances[MAXN], ncount[MAXN], edgecost[MAXN][MAXD], graph[MAXN][MAXD], order[MAXT];
unsigned nodes, edges, num_treasures, a, b, c, budget;

int check(){
	int cur = num_treasures, sum = 0;
	for( int i = 0; i < num_treasures; ++i ){
		sum += table[cur][order[i]];
		if( sum + table[cur][num_treasures] > budget ){
			return i+1;
		}
		cur = order[i];
	}
	return num_treasures+1;
}

int bt( int at, int collected, int budget ){
	for( int i = 0; i < num_treasures; ++i ){
		order[i] = i;
	}
	int maxi = 1;
	while( next_permutation( order, order + num_treasures ) ){
		maxi = max( maxi, check() );
	}
	return maxi;
}

void calcTable(int src, int row ){
	fill( distances, distances + nodes, numeric_limits<int>::max()/2);
	typedef pair<int,int> pii;
	priority_queue< pii, vector<pii>, greater<pii> > que;
	que.push( make_pair(0,src) );
	distances[src] = 0;
	while( !que.empty() ){
		int top = que.top().second, key = que.top().first;
		que.pop();
		if( key == distances[top] ){
			for( int i = 0; i < ncount[top]; ++i ){
				int new_key = key + edgecost[top][i];
				if( new_key < distances[graph[top][i]] ){
					distances[graph[top][i]] = new_key;
					que.push( make_pair(new_key,graph[top][i]) );
				}
			}
		}
	}

	for( unsigned i = 0; i <= num_treasures; ++i ) table[row][i] = distances[treasures[i]];
}

int main( int argc, char ** args ){
	cin >> nodes; // skip the number of cases
	while( cin >> nodes >> edges ){
		memset( ncount, 0, nodes * sizeof(int) );
		for( unsigned i = 0; i < edges; ++i ){
			cin >> a >> b >> c;
			graph[a][ ncount[a] ] = b;
			edgecost[a][ ncount[a] ] = c;
			graph[b][ ncount[b] ] = a;
			edgecost[b][ ncount[b] ] = c;
			++ncount[a];
			++ncount[b];			
		}
		cin >> num_treasures;
		for( unsigned i = 0; i < num_treasures; ++i ) cin >> treasures[i];
		treasures[num_treasures] = 0;
		for( unsigned i = 0; i <= num_treasures; ++i ) calcTable( treasures[i], i );
		cin >> budget;
		table[num_treasures ][num_treasures ] = 0;
		cout << bt(num_treasures, 0, budget) - 1 << endl;
	}
	return 0;
}
