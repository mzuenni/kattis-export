// @EXPECTED_RESULTS@: WRONG-ANSWER

#include <iostream>
#include <queue>
#include <cstring>
#include <limits>
#include <utility>

using namespace std;

#define MAXN 10000
#define MAXD 10
#define MAXT 8

int treasures[MAXT], table[MAXT+1][MAXT+1], distances[MAXN], count[MAXN], edgecost[MAXN][MAXD], graph[MAXN][MAXD];
unsigned nodes, edges, num_treasures, a, b, c, budget;

int bt( int at, int collected, int budget ){
	if( table[num_treasures][at] > budget ){
		return 0;
	}

	unsigned int min_cost = -1;
	int best = 0;
	for( int i = 0; i < num_treasures; ++i ){
		if( !(collected & (1<<i)) && table[at][i] < min_cost ){
			min_cost = table[at][i];
			best = i;
		}
	}
	if( min_cost != -1 ){
		return 1 + bt( best, collected | (1<<best), budget - table[at][best] );
	} else {
		return 1;
	}
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
			for( int i = 0; i < count[top]; ++i ){
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
		memset( count, 0, nodes * sizeof(int) );
		for( unsigned i = 0; i < edges; ++i ){
			cin >> a >> b >> c;
			graph[a][ count[a] ] = b;
			edgecost[a][ count[a] ] = c;
			graph[b][ count[b] ] = a;
			edgecost[b][ count[b] ] = c;
			++count[a];
			++count[b];			
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
