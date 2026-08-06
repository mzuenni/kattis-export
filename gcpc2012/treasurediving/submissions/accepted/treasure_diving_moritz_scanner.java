// @EXPECTED_RESULTS@: CORRECT
import java.util.*;

public class treasure_diving_moritz_scanner{
	public static final int MAXN = 10000;
	public static final int MAXT = 8;
	public static final int MAXD = 10;
	public static final int INF = 2147483647;

	static int treasures[];
	static int count[];
	static int graph[][];
	static int cost[][];
	static int distances[];
	static int table[][];

	public static class pair implements Comparable<pair>{
		public int first;
		public int second;

		public int compareTo( pair p ){
			if( first < p.first )
				return -1;
			if( first > p.first )
				return 1;
			if( second < p.second )
				return -1;
			if( second > p.second )
				return 1;
			return 0;
		}
	}

	public static void calcTable( int nodes, int num_treasures ){
		for( int i = 0; i <= num_treasures; ++i ){
			PriorityQueue<pair> que = new PriorityQueue<pair>();
			pair initial = new pair();
			initial.first = 0;
			initial.second = treasures[i];			
			que.add( initial );
			for( int n = 0; n < nodes; ++n ){
				distances[n] = INF;
			}
			distances[treasures[i]] = 0;
			while( que.size() > 0 ){
				pair current = que.poll();
				if( distances[current.second] == current.first ){
					for( int n = 0; n < count[current.second]; ++n ){
						if( (current.first + cost[current.second][n]) < distances[ graph[current.second][n] ] ){
							distances[ graph[current.second][n] ] = (current.first + cost[current.second][n]);
							pair new_pair = new pair();
							new_pair.first = (current.first + cost[current.second][n]);
							new_pair.second = graph[current.second][n];
							que.add( new_pair );
						}
					}
				}
			}
			for( int t = 0; t <= num_treasures; ++t ){
				table[i][t] = distances[treasures[t]];
			}
		}
	}

	public static int solve( int at, int collected, int num_treasures, int budget ){
		if( budget < table[num_treasures][at] )
			return 0;
		int best = 0;
		for( int i = 0; i < num_treasures; ++i ){
			if( table[at][i] != INF && ( 0 == (collected & (1<<i)))){
				int tmp = solve( i, collected | (1<<i), num_treasures, budget - table[at][i] );
				if( tmp > best )
					best = tmp;
			}
		}
		return 1 + best;
	}
	
	public static void main( String[] args ){
		treasures = new int[MAXT+1];
		count = new int[MAXN];
		graph = new int[MAXN][MAXD];
		cost = new int[MAXN][MAXD];
		distances = new int[MAXN];
		table = new int[MAXT+1][MAXT+1];
		Scanner scanner = new Scanner( System.in );
		scanner.nextInt(); // skip number of cases
		while( scanner.hasNextInt() ){
			int nodes, edges;
			nodes = scanner.nextInt();
			edges = scanner.nextInt();
			for( int i = 0; i < nodes; ++i ){
				count[i] = 0;
			}
			for( int e = 0; e < edges; ++e ){
				int from, to, c;
				from = scanner.nextInt();
				to = scanner.nextInt();
				c = scanner.nextInt();
				graph[from][count[from]] = to;
				cost[from][count[from]] = c;
				count[from]++;

				graph[to][count[to]] = from;
				cost[to][count[to]] = c;
				count[to]++;
			}
			int num_treasures = scanner.nextInt();
			for( int t = 0; t < num_treasures; ++t ){
				treasures[t] = scanner.nextInt();
			}
			treasures[num_treasures] = 0;
			int budget = scanner.nextInt();
			calcTable( nodes, num_treasures );
			System.out.println( solve( num_treasures, 0, num_treasures, budget )-1 );
		}
	}
}
