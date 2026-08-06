// @EXPECTED_RESULTS@: CORRECT

import java.util.*;
import java.io.*;

public class treasure_diving_moritz_strtok{
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
	
	public static void main( String[] args ) throws IOException {
		treasures = new int[MAXT+1];
		count = new int[MAXN];
		graph = new int[MAXN][MAXD];
		cost = new int[MAXN][MAXD];
		distances = new int[MAXN];
		table = new int[MAXT+1][MAXT+1];
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String line = reader.readLine();
		line = reader.readLine(); // skip number of cases
		// Scanner scanner = new Scanner( System.in );
		while( line != null) {
			int nodes, edges;
			StringTokenizer strtok = new StringTokenizer(line);
			nodes = Integer.parseInt(strtok.nextToken());
			edges = Integer.parseInt(strtok.nextToken());
			for( int i = 0; i < nodes; ++i ){
				count[i] = 0;
			}
			for( int e = 0; e < edges; ++e ){
				int from, to, c;
				line = reader.readLine();
				strtok = new StringTokenizer(line);
				from = Integer.parseInt(strtok.nextToken());
				to = Integer.parseInt(strtok.nextToken());
				c = Integer.parseInt(strtok.nextToken());
				graph[from][count[from]] = to;
				cost[from][count[from]] = c;
				count[from]++;

				graph[to][count[to]] = from;
				cost[to][count[to]] = c;
				count[to]++;
			}
			line = reader.readLine();
			int num_treasures = Integer.parseInt(line);
			line = reader.readLine();
			strtok = new StringTokenizer(line);
			for( int t = 0; t < num_treasures; ++t ){
				treasures[t] = Integer.parseInt(strtok.nextToken());
			}
			treasures[num_treasures] = 0;
			line = reader.readLine();
			int budget = Integer.parseInt(line);
			calcTable( nodes, num_treasures );
			System.out.println( solve( num_treasures, 0, num_treasures, budget )-1 );
			
			line = reader.readLine();
		}
	}
}
