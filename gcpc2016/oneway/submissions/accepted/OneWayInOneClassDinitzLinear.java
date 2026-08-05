import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class OneWayInOneClassDinitzLinear {
	FlowNetwork fn;
	int[] indegrees;
	
	static class Dinitz {
		private final int[] Q;
		private final int[] dist;
		protected long maxFlow = 0;
		protected final FlowNetwork fn;
		protected final int[][] f;
	  
		public Dinitz(FlowNetwork fn) {
			this.fn = fn;
			this.f = new int[fn.adj.length][];
			for (int i = 0; i < fn.adj.length; i++) {
				this.f[i] = new int[fn.adj[i].length];
			}
			this.Q = new int[this.fn.n];
			this.dist = new int[this.fn.n];
		}

	  private boolean dinicBfs(int src, int dest) {
	    Arrays.fill(dist, -1);
	    dist[src] = 0;
//	    Arrays.fill(this.Q, 0);	// XXX not necessary since we start overwriting from the beginning.
	    int sizeQ = 0;
	    Q[sizeQ++] = src;
	    for (int i = 0; i < sizeQ; i++) {
	      int u = Q[i];
	      for (int j = 0; j < this.fn.adj[u].length; j++) {
	        if (dist[this.fn.adj[u][j]] < 0 && this.f[u][j] < this.fn.cap[u][j]) {
	          dist[this.fn.adj[u][j]] = dist[u] + 1;
	          Q[sizeQ++] = this.fn.adj[u][j];
	        }
	      }
	    }
	    return dist[dest] >= 0;
	  }

	  private int dinicDfs(int[] ptr, int dest, int u, int f) {
	    if (u == dest)
	      return f;
	    for (; ptr[u] < this.fn.adj[u].length; ++ptr[u]) {
	      if (dist[this.fn.adj[u][ptr[u]]] == dist[u] + 1 && this.f[u][ptr[u]] < this.fn.cap[u][ptr[u]]) {
	        final int df = dinicDfs(ptr, dest, this.fn.adj[u][ptr[u]], Math.min(f, this.fn.cap[u][ptr[u]] - this.f[u][ptr[u]]));
	        if (df > 0) {
	          this.f[u][ptr[u]] += df;
	          this.f[this.fn.adj[u][ptr[u]]][this.fn.posInAdj[u][ptr[u]]] -= df;
	          return df;
	        }
	      }
	    }
	    return 0;
	  }
	  
	  public long maxFlow(int src, int dest) {
		    while (dinicBfs(src, dest)) {
		      int[] ptr = new int[this.fn.n];
		      while (true) {
		        final int df = dinicDfs(ptr, dest, src, Integer.MAX_VALUE);
		         if (df == 0)
		          break;
		        maxFlow += df;
		      }
		    }
		    return maxFlow;
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
	
	public OneWayInOneClassDinitzLinear(FlowNetwork fn, int[] indegrees) {
		this.fn = fn;
		this.indegrees = indegrees;
	}
	
	public static final int ceil(final double x) {
		return (int)Math.ceil(x);
	}
	
	
	public int orientationNumberLinearSearch() {
		int test = 0;
//		int upper = fn.n-2;
		int upper = 0;
		for (int d : indegrees) {
			upper = Math.max(upper, d);	// clearly, the maximum indegree of the initial orientation is an upper bound (and usually much better than n)
		}
		int minFeasible = upper;
		upper--;	// as upper is feasible, it should not be tested again.
		Dinitz fa = new Dinitz(fn);
		LINEAR:
		while (test <= upper) {
			fn.updateSourceAndSinkCapacitiesKowalik(test, indegrees);
			fa.clearFlow();
			if (fa.maxFlowKowalik()) {
				minFeasible = test;
				break LINEAR;
			}
			else {
				test++;
			}
		}
		return minFeasible;
	}
	
	

	public static void main(final String[] args) {
		String line;
		long start;
		long end;
		try {
			final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			line = br.readLine();
			final int n = Integer.parseUnsignedInt(line);
			line = br.readLine();
			final int m  = Integer.parseUnsignedInt(line);
			start = System.currentTimeMillis();
			ArrayList<Integer>[] ad = (ArrayList<Integer>[]) new ArrayList[n];	// *ahem*
			for (int i = 0; i < n; i++) {
				ad[i] = new ArrayList<>();
			}
			for (int i = 0; i < m; i++) {
				line = br.readLine();
				int blankPos = line.indexOf(' ');
				int u = Integer.parseUnsignedInt(line.substring(0, blankPos))-1;
				int v = Integer.parseUnsignedInt(line.substring(blankPos+1))-1;
//				System.out.println(u+", "+v);
//				assert(u < v);
				ad[u].add(Integer.valueOf(v));
				ad[v].add(Integer.valueOf(u));
			}
			br.close();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for reading the graph.");
			start = System.currentTimeMillis();
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
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for setting adjacency and capacity of the flow network.");
//			System.out.println("Generate rev. indexing scheme.");
			// generate reverse indexing scheme
			start = System.currentTimeMillis();
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
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for back-indexing.");
			FlowNetwork fn = new FlowNetwork(adj, posInAdj, cap);
			OneWayInOneClassDinitzLinear ow = new OneWayInOneClassDinitzLinear(fn, indegrees);
//			System.out.println("Start the search.");
//			int orientationNumber = ow.orientationNumberBinarySearch();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for reading the graph.");
			start = System.currentTimeMillis();
			int orientationNumber = ow.orientationNumberLinearSearch();
//			int orientationNumber = ow.orientationNumberBinarySearch();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for computing the orientation number:");
			System.out.println(orientationNumber);
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
