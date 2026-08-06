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

int treasures[MAXT], table[MAXT+1][MAXT+1], distances[MAXN], ncount[MAXN], edgecost[MAXN][MAXD], graph[MAXN][MAXD];
unsigned nodes, edges, num_treasures, a, b, c, budget;

int bt( int at, int collected, int budget ){
	std::vector< int > treasure_cost;
	for( int i = 0; i < num_treasures; ++i ){
		treasure_cost.push_back( 2 * table[num_treasures][treasures[i]] );
	}
	int itcount = 1;
	for( int i = 2; i <= num_treasures; ++i ){
		itcount *= i;
	}
	sort( treasure_cost.begin(), treasure_cost.end() );
	int best = 0;
	for( int i = 0; i < itcount; ++i ){
		int cost = 0, j;
		for( j = 0; j < num_treasures && cost <= budget; ++j ){
			cost += treasure_cost[j];
		}
		best = max( best, j - (cost > budget) );
		next_permutation( treasure_cost.begin(), treasure_cost.end() );
	}
	return best;
}

void calcTable(int src, int row ){
	fill( distances, distances + nodes, numeric_limits<int>::max());
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

	for( unsigned i = 0; i < num_treasures; ++i ) table[row][i] = distances[treasures[i]];
	table[row][num_treasures] = distances[0];
}

int main( int argc, char ** args ){
	cin >> nodes; // skip number of cases
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
		calcTable( 0, num_treasures );
		for( unsigned i = 0; i < num_treasures; ++i ) calcTable( treasures[i], i );
		cin >> budget;
		table[num_treasures ][num_treasures ] = 0;
		cout << bt(num_treasures, 0, budget) - 1 << endl;
	}
	return 0;
}
