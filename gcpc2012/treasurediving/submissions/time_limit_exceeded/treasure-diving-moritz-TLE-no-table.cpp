// @EXPECTED_RESULTS@: TIMELIMIT

#include <iostream>
#include <queue>
#include <cstring>
#include <limits>
#include <utility>

using namespace std;

#define MAXN 10000
#define MAXD 10
#define MAXT 8

int treasures[MAXT+1], distances[MAXN], count[MAXN], edgecost[MAXN][MAXD], graph[MAXN][MAXD];
unsigned nodes, edges, num_treasures, a, b, c, budget;

int getDistance( int src, int tgt ){
	fill( distances, distances + nodes, numeric_limits<int>::max());
	typedef pair<int,int> pii;
	priority_queue< pii, vector<pii>, greater<pii> > que;
	que.push( make_pair(0,src) );
	distances[src] = 0;
	while( !que.empty() ){
		int top = que.top().second, key = que.top().first;
		if( top == tgt ){
			return key;
		}
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
	return numeric_limits<int>::max();
}

int bt( int at, int collected, int budget ){
	if( budget < getDistance( treasures[at], 0 ) ){
		return 0;
	}
	int best = 0, distance;
	for( int i = 0; i < num_treasures; ++i )
		if( (!(collected & (1<<i))) && ((distance = getDistance( treasures[at], treasures[i] )) != std::numeric_limits<int>::max() ) )
			best = max( best, bt( i, collected | (1<<i), budget - distance ) );
	return 1 + best;
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
		for( int i = 0; i < num_treasures; ++i ){
			cin >> treasures[i];
		}
		treasures[num_treasures] = 0;
		cin >> budget;
		cout << bt(num_treasures, 0, budget) - 1 << endl;
	}
	return 0;
}
