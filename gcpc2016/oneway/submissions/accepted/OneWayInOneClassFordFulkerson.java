import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class OneWayInOneClassFordFulkerson {
	FlowNetwork fn;
	int[] indegrees;
	
	static class FordFulkerson {
		final boolean[] visited;
		protected long maxFlow = 0;
		protected final FlowNetwork fn;
		protected final int[][] f;
	  
		public FordFulkerson(FlowNetwork fn) {
			this.fn = fn;
			this.f = new int[fn.adj.length][];
			for (int i = 0; i < fn.adj.length; i++) {
				this.f[i] = new int[fn.adj[i].length];
			}
			this.visited = new boolean[fn.adj.length];
		}
		/**
		 * Compute the max-flow using the Ford-Fulkerson algorithm and stores it in the matrix F.
		 * @param s the source node
		 * @param t the sink node
		 */
		public long maxFlow(int s, int t) {	
		  // Visited array to perform DFS, initially empty
			Arrays.fill(visited, false);
			// Repeat until there is no path
			int value;
			do {
				value = dfs(s,t, Integer.MAX_VALUE);
				maxFlow += value;
				Arrays.fill(visited, false);
			}
			while (value > 0);
			return maxFlow;
		}

		/*
		 * Performs a DFS starting from node i and trying to reach node t. Nodes already visited are
		 * stored in the boolean vector visited.
		 *  
		 * @param u the current node
		 * @param t the sink node
		 * @param visited the boolean set containing the nodes that have been visited
		 * @param the smallest capacity found so far.
		 * @returns the value of the additional flow found during this DFS, or 0 if there the sink
		 * is not reachable from the source.
		 */
		private int dfs(int u, int t, int min) {
			// If sink has been reached, terminate
			if (u == t) {
				return min;
			}
			visited[u] = true;
			for (int j = 0; j < fn.adj[u].length; j++) {
				int v = fn.adj[u][j];
				int diff = fn.cap[u][j] - f[u][j];
				if (diff > 0 && !visited[v]) {
					// Recursively perform the DFS, using the capacity of edge (i,v) if smaller than the
					// min found so far.
					
					int df = dfs(v, t, Math.min(min, diff));
					
					// If df > 0, we have found the sink, and df is the maximum value of the flow along the
					// path connecting the source and sink. We update both the capacities and the flow
					// accordingly.
					if (df > 0) {
						f[u][j] = f[u][j] + df;
						f[v][fn.posInAdj[u][j]] = f[v][fn.posInAdj[u][j]] - df;
						return df;
					}
				}
			}
			// The sink has not been found.
			return 0;
		}
	  
	  public void clearFlow() {
			for (int[] f : this.f) {
				Arrays.fill(f, 0);
			}
			this.maxFlow = 0;
		}
		
		public boolean sourceArcsSatisfied(final int s) {
			long capSourceArcs = 0;	// the value of the cut ({s}, V\{s})
			for (final int c : this.fn.cap[s]) {
				capSourceArcs += c;
			}
			if (this.maxFlow == capSourceArcs)
				return true;
			return false;
		}
		
		public boolean maxFlowKowalik() {
			this.maxFlow(fn.n-2, fn.n-1);	// index of source and sink fixed!
			return this.sourceArcsSatisfied(fn.n-2);
		}
	}
	
	static class FlowNetwork {
		public final int n;		// typically n-2 = source, n-1 = sink
		final int[][] adj;
		final int[][] posInAdj;
		public final int[][] cap;
		
		public FlowNetwork(final int[][] adj, final int[][] posInAdj, final int[][] cap) {
			this.n = adj.length;
			this.adj = adj;
			this.posInAdj = posInAdj;
			this.cap = cap;
		}
		
		public void updateSourceAndSinkCapacitiesKowalik(final int d, final int[] indegrees) {
			// Update. Note that index of s and t is fixed.
			for (int u = 0; u < this.n-2; u++) {
				this.cap[this.n-2][u] = Math.max(0, indegrees[u]-d);				// from source
				this.cap[u][this.cap[u].length-1] = Math.max(0, d-indegrees[u]);	// to target
			}
		}
		
		public void setCap(final int u, final int posInUAdj, final int cap) {
			this.cap[u][posInUAdj] = cap;
		}
	}
	
	public OneWayInOneClassFordFulkerson(FlowNetwork fn, int[] indegrees) {
		this.fn = fn;
		this.indegrees = indegrees;
	}
	
	public static final int ceil(final double x) {
		return (int)Math.ceil(x);
	}
	
	public int orientationNumberBinarySearch() {
		int lower = 0;
//		int upper = fn.n-2;
		int upper = 0;
		for (int d : indegrees) {
			upper = Math.max(upper, d);	// clearly, the maximum indegree of the initial orientation is an upper bound (and usually much better than n)
		}
		int minFeasible = upper;
		upper--;	// as upper is feasible, it should not be tested again.
		FordFulkerson fa = new FordFulkerson(fn);
		while (upper-lower >= 0) {
//			System.out.println("lower = "+lower+", upper = "+upper);
			int dTest = ceil(0.5*(upper+lower));
//			System.out.println("dTest = "+dTest);
			fn.updateSourceAndSinkCapacitiesKowalik(dTest, indegrees);
			fa.clearFlow();
			if (fa.maxFlowKowalik()) {
				minFeasible = dTest;
				upper = dTest-1;
			}
			else {
				lower = dTest+1;
			}
		}
		
		return minFeasible;
	}

	public static void main(final String[] args) {
		String line;
		try {
			final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			line = br.readLine();
			final int n = Integer.parseInt(line);
			line = br.readLine();
			final int m  = Integer.parseInt(line);
			
			ArrayList<Integer>[] ad = (ArrayList<Integer>[]) new ArrayList[n];	// *ahem*
			for (int i = 0; i < n; i++) {
				ad[i] = new ArrayList<>();
			}
			for (int i = 0; i < m; i++) {
				line = br.readLine();
				String[] split = line.split(" ");
				int u = Integer.parseInt(split[0])-1;
				int v = Integer.parseInt(split[1])-1;
//				System.out.println(u+", "+v);
				assert(u < v);
				ad[u].add(v);
				ad[v].add(u);
			}
			for (ArrayList<Integer> al : ad) {
				Collections.sort(al);	// for later use XXX
//				System.out.println(al);
			}
			int[] indegrees = new int[n];
			int[][] adj = new int[n+2][];	// I'm a big fan of primitive data types and arrays...
			int[][] cap = new int[n+2][];
			
			// NOTE: source and sink arc capacities will be set for each test in the search, here we only allocate.
			for (int i = 0; i < n; i++) {
				adj[i] = new int[ad[i].size()+2];	// one from source, one to sink
				cap[i] = new int[ad[i].size()+2];
				for (int j = 0; j < ad[i].size(); j++) {
					adj[i][j] = ad[i].get(j).intValue();
				}
				adj[i][adj[i].length-2] = n;		// source index
				adj[i][adj[i].length-1] = n+1;		// sink index
				// set capacities
				for (int j = 0; j < ad[i].size(); j++) {
					int v = adj[i][j];
					if (i < v) {
						indegrees[i]++;	// arbitrarily orient edges to the vertex with smaller degree
						cap[i][j] = 1;	// we can re-orient: cap 1. The other direction is correct with cap. 0
					}
				}
			}
			// We are a bit lazy: every vertex has arcs from and to the source/sink
			adj[n] = new int[n];
			cap[n] = adj[n].clone();	// all zeroes
			cap[n+1] = adj[n].clone();	// all zeroes
			for (int i = 0; i < n; i++) {
				adj[n][i] = i;
			}
			adj[n+1] = adj[n].clone();	// same
//			System.out.println("Generate rev. indexing scheme.");
			// generate reverse indexing scheme
			int[][] posInAdj = new int[n+2][];
			posInAdj[n] = new int[n];
			posInAdj[n+1] = new int[n];
			for (int i = 0; i < n; i++) {
				posInAdj[i] = new int[adj[i].length];
				posInAdj[i][adj[i].length-2] = i;
				posInAdj[i][adj[i].length-1] = i;
				posInAdj[n][i] = adj[i].length-2;
				posInAdj[n+1][i] = adj[i].length-1;
			}
			// Now the actual graph adjacency
			int[] greaterPos = new int[n];
			for (int u = 0; u < n; u++) {
				for (int j = 0; j < adj[u].length-2; j++) {	// all except source and target (sink)
					final int v = adj[u][j];
					if (u < v)	// one search suffices for two directions!
						break;	// instead of continue, break can be used, since any following vertex has an even higher index (we sorted, remember?)
					// Now, u > v.
					while (adj[v][greaterPos[v]] != u) {
						greaterPos[v]++;
					}
					// Any vertex after u must be even greater!
					posInAdj[u][j] = greaterPos[v];
					posInAdj[v][greaterPos[v]] = j;
				}
			}
			FlowNetwork fn = new FlowNetwork(adj, posInAdj, cap);
			OneWayInOneClassFordFulkerson ow = new OneWayInOneClassFordFulkerson(fn, indegrees);
//			System.out.println("Start the search.");
			int orientationNumber = ow.orientationNumberBinarySearch();
			System.out.println(orientationNumber);
			
			br.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
