import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;

public class OneWayInOneClassPushRelabel {
	FlowNetwork fn;
	int[] indegrees;
	
	static class PrimitiveQueue {
		private final int[] arr;
		private int startPtr = 0;
		private int endPtr = 0;
		
		public PrimitiveQueue(final int cap) {
			this.arr = new int[cap];
		}
		
		public void addLast(final int a) {
			this.arr[this.endPtr++] = a;
		}
		
		public int removeFirst() {
			return this.arr[startPtr++];
		}
		
		public boolean isEmpty() {
			return (this.startPtr == this.endPtr);
		}
		
		public void clear() {
			this.startPtr = 0;
			this.endPtr = 0;
		}
	}
	
	/**
	 * Performs Push-Relabel with Highest-Label Selection Rule. This runs in O(|V|^2 \sqrt(|E|)) (Cheriyan and Maheswari 1987)
	 * We can periodically perform a BFS update of the distance labeling ('global relabeling heuristic'). Doing this about every |V| relabelings does not impair performance asymptotically.
	 * We further use the gap heuristic (Derigs and Meier).
	 * @author mablumen
	 *
	 */
	static class PushRelabel {
		public static final boolean useGapHeuristic = false;
		public static final boolean useGlobalRelabelingHeuristic = true;
		
		final int[] posOfActiveEdge;
		final int[] numInactive;
		final boolean[] inactive;		// use a boolean array to quickly lookup whether a vertex is inactive
		final LinkedList<Integer>[] active;	// for every possible height, we maintain a bucket of currently active vertices
		int mu;		// pointer to highest nonempty active bucket
		int[] d;
		final long[] e;
		int s;
		int t;
		final FlowNetwork fn;
		public final int[][] f;
		
		final boolean[] visited;
		final PrimitiveQueue q;
		
//		int D;	// below this layer, all vertices are in BFS order (from the sink). Use for the incremental-start heuristic variant of global relabeling.
		long opsDone;
		
		public PushRelabel(FlowNetwork fn) {
			this.fn = fn;
			this.f = new int[fn.adj.length][];
			for (int i = 0; i < fn.adj.length; i++) {
				this.f[i] = new int[fn.adj[i].length];
			}
			this.opsDone = 0;
			this.d = new int[fn.adj.length];
			this.e = new long[fn.adj.length];
			this.e[fn.n-2] = Long.MAX_VALUE;	// source excess
			this.numInactive = new int[fn.adj.length+1];
			this.inactive = new boolean[fn.adj.length];
			this.posOfActiveEdge = new int[fn.adj.length];	// correctly initialized with zeroes
			this.active = new LinkedList[fn.adj.length];
			
			// For BFS purposes -- avoid re-allocations!
			this.visited = new boolean[this.fn.n];
			this.q = new PrimitiveQueue(this.fn.n);
			
			for (int i = 0; i < this.fn.n; i++) {
				this.active[i] = new LinkedList<Integer>();
			}
		}
		
		public void clearFlow() {
			for (int[] f : this.f) {
				Arrays.fill(f, 0);
			}
			this.opsDone = 0;
			Arrays.fill(this.d, 0);
			Arrays.fill(this.e, 0L);
			this.e[fn.n-2] = Long.MAX_VALUE;	// source excess
			Arrays.fill(this.numInactive, 0);
			Arrays.fill(this.inactive, false);
			Arrays.fill(this.posOfActiveEdge, 0);
			Arrays.fill(this.visited, false);
			this.q.clear();
			for (int i = 0; i < this.fn.n; i++) {
				this.active[i].clear();
			}
		}
		
		public void setSourceAdjLengthAndClear(final int sourceID, final int length) {
			this.clearFlow();
			this.f[sourceID] = new int[length];	// initialized with 0s
		}
		
		/**
		 * Set preflow as in Introduction to Algorithms.
		 */
		public void preFlow() {
			for (int j = 0; j < this.fn.adj[this.s].length; j++) {
				final int u = this.fn.adj[this.s][j];
				this.f[s][j] = this.fn.cap[s][j];
				this.f[u][this.fn.posInAdj[s][j]] = -this.fn.cap[s][j];
				this.e[u] = this.f[s][j];	// there can be only one ingoing arc from the source
			}
			// Do not change the source's excess: it's infinite.
		}
		
		public void discharge(final int v) {
			int w = this.fn.adj[v][this.posOfActiveEdge[v]];
			boolean endOfList = false;
			do {
				if (this.isAdmissible(v, w, this.posOfActiveEdge[v])) {
					this.push(v, w, this.posOfActiveEdge[v]);
				}
				else {
					if (this.posOfActiveEdge[v] < (this.fn.adj[v].length-1) ) {	// not the last edge?
						this.posOfActiveEdge[v]++;
						w = this.fn.adj[v][this.posOfActiveEdge[v]];	// replace edge by next edge
					}
					else {			// (u,w) is the last edge
						this.posOfActiveEdge[v] = 0;
						w = this.fn.adj[v][this.posOfActiveEdge[v]];	// actually, you could use this.fn.adj[v][0]
						endOfList = true;
					}
				}
			}
			while (this.e[v] >= 1 && !endOfList);
			
			if (endOfList) {
				this.relabel(v);
			}
			else if (this.e[v] == 0) {
				// has already been removed from the active bucket.
				this.inactive[v] = true;
				this.numInactive[d[v]]++;
			}
		}
		
		public void push(final int v, final int w, final int posWInV) {
			final long residualCap = this.fn.cap[v][posWInV]-this.f[v][posWInV];
			final long send = Math.min(this.e[v], residualCap);
			this.f[v][posWInV] += send;
			this.f[w][this.fn.posInAdj[v][posWInV]] -= send;
			this.e[v] -= send;
			this.e[w] += send;
			
//			if (send >= 1) {
//				this.D = Math.min(this.D, this.d[w]);
//			}
			if (isNowActive(w) && inactive[w]) {	// w becomes active!
				this.inactive[w] = false;
				this.numInactive[d[w]]--;
				this.active[this.d[w]].addLast(w);
				if (this.d[w] > this.mu)
					this.mu = this.d[w];
			}
		}
		
		public void relabel(final int v) {
			// set inactive by default. The layer where it is will be set later, if applicable. If the new height is less than fn.n, set it active again!
			this.inactive[v] = true;	// true

			int min = this.fn.n;
			for (int j = 0; j < this.fn.adj[v].length; j++) {
				final int w = this.fn.adj[v][j];	// Cormen: v
				final int residualCap = this.fn.cap[v][j]-this.f[v][j];
				if (residualCap >= 1) {
					if (this.d[w] < min)
						min = this.d[w];
				}
			}
			if (min != this.fn.n) {
				min++;
			}
			this.d[v] = min;
			
			if (isNowActive(v)) {
				this.inactive[v] = false;
				this.active[d[v]].addLast(v);	// since active, d[v] cannot be fn.n-1
				if (d[v] > this.mu)	// != fn.n, since active
					this.mu = this.d[v];
			}
			else {
				this.numInactive[d[v]]++;
			}
//			if (useGapHeuristic && this.d[v] < this.fn.n && this.d[v] > 0) {
//				if (this.active[d[v]-1].isEmpty() && this.numInactive[d[v]-1] == 0) {
//					// Visit every layer d[v], ..., fn.n-1 and delete all vertices!
//					for (int i = d[v]; i < this.fn.n; i++) {
//						Iterator<Integer> it = this.active[i].iterator();
//						this.numInactive[this.fn.n] += this.active[i].size();
//						while (it.hasNext()) {
//							final int w = it.next();
//							this.inactive[w] = true;
//							this.d[w] = this.fn.n;
//						}
//						this.numInactive[i] = 0;
//						this.active[i].clear();
//					}
//				}
//			}
//			if (useGapHeuristic && this.d[v] < this.fn.n && this.d[v] > 0) {
//				if (this.active[d[v]-1].isEmpty() && this.numInactive[d[v]-1] == 0) {
//					// z = d[v]-1 is a gap as there exists a vertex whose distance is higher than z (but not equal to n). Derigs&Meier => lift vertices with d[v] or higher to level n!
//					// inactive vertices
//					int count = 0;
//					for (int node = 0; node < this.fn.n-1; node++) {
//						if (inactive[node] && d[node] >= d[v] && d[node] != this.fn.n) {	// not in an 'active' list.
//							this.numInactive[d[node]]--;
//							d[node] = this.fn.n;
//							this.numInactive[this.fn.n]++;
//							count++;
//						}
//					}
//					System.out.println("Removed "+count+" inactive vertices.");
//					// #inactive per level can be updated in the next loop
//					
//					count = 0;
//					// active vertices
//					System.out.println("The gap level is "+d[v]+", v's level is "+d[v]+", level size is "+this.active[d[v]].size());
//					for (int level = d[v]; level < this.fn.n; level++) {
//						Iterator<Integer> it = this.active[level].iterator();
//						this.numInactive[this.fn.n] += this.active[level].size();
//						while (it.hasNext()) {
//							final int w = it.next();
//							this.d[w] = this.fn.n;
//							this.inactive[w] = true;
//							count++;
//						}
////						this.numInactive[i] = 0;	// faster than update in previous loop
//						this.active[level].clear();
//						assert(this.active[level].size() == 0);
//					}
//					System.out.println("Removed "+count+" active vertices.");
//					
//				}
//			}
			
			this.opsDone++;
		}
		
		public boolean isAdmissible(final int v, final int w, final int wInVPos) {
			final boolean downhill = (this.d[v] == this.d[w] + 1);
			final boolean residual = (this.f[v][wInVPos] < this.fn.cap[v][wInVPos]);	// also if flow negative (residual!)
			return (downhill && residual);
		}

		public boolean isNowActive(final int v) {
			boolean excessPos = (this.e[v] >= 1);
			boolean notSource = (v != this.s);
			boolean notTarget = (v != this.t);
			boolean finiteDist = (d[v] < this.fn.n);
			return (excessPos && notSource && notTarget && finiteDist);
		}
		
		public void globalRelabelingHeuristic() {
			this.d = distanceByBackwardBFS();
		}
		
		public int[] distanceByBackwardBFS() {
			final int target = this.t;
			Arrays.fill(this.visited, false);
			q.clear();
			q.addLast(target);
			visited[target] = true;
			
			final int[] distance = new int[this.fn.n];
			Arrays.fill(distance, this.fn.n);		// for unreachable vertices
			distance[target] = 0;
			
			while (!q.isEmpty()) {
				final int vertex = q.removeFirst();
				final int d = distance[vertex];
				for (int j = 0; j < this.fn.adj[vertex].length; j++) {	// all neighbors
					final int neighb = this.fn.adj[vertex][j];
					if (this.f[neighb][this.fn.posInAdj[vertex][j]] == this.fn.cap[neighb][this.fn.posInAdj[vertex][j]])	// cannot go further through residual network
						continue;
					if (!visited[neighb] && this.d[neighb] != this.fn.n) {
						q.addLast(neighb);							// add to queue
						visited[neighb] = true;
						distance[neighb] = d+1;
					}
				}
			}
			distance[target-1] = this.fn.n;	// source label.
			return distance;
		}
		
		
		public long maxFlow(final int s, final int t) {
			this.s = s;
			this.t = t;
			this.preFlow();
			// The following initial distance relabeling is done via a backward BFS on the sink t. The source's distance is manually set to n.
//			this.d = distanceByBackwardBFS().clone();
			this.globalRelabelingHeuristic();
			this.d[s] = this.fn.n;		// no need to discharge the source.
//			this.d[t] = 0;	// senseless, I guess
//			this.D = this.fn.n;
			this.inactive[t] = true;
			this.numInactive[0] = 1;
			this.inactive[s] = true;
			this.numInactive[this.fn.n] = 1;
			
			return this.maxFlowHighestLabelRule();
		}
		
		public long maxFlowHighestLabelRule() {
			int maxD = -1;
			for (int i = 0; i < this.s; i++) {	// exclude s, t
				if (isNowActive(i)) {
					this.active[this.d[i]].addLast(i);
					if (this.d[i] > maxD)
						maxD = this.d[i];
				}
				else {
					this.inactive[i] = true;
					this.numInactive[this.d[i]]++;
				}
			}
			this.mu = maxD;		// maximum height
			
			// Max-distance rule: push-relabel runs in O(|V|^2 \sqrt(|E|))
			ACTIVE_VERTEX_EXISTS:
			while (this.mu >= 0) {
				while (this.active[this.mu].isEmpty()) {
					this.mu--;
					if (this.mu == 0)
						break ACTIVE_VERTEX_EXISTS;
				}
				final int v = this.active[this.mu].removeFirst();	// Note that in the paper "Two-Level Push-Relabel Algorithm for the Maximum Flow Problem", Goldberg says that this is only removed after the push (discharge?) operations have reduced the excess to zero. However, we always remove the first vertex and add it again if it is not fully discharged.
				this.discharge(v);
				
				if (useGlobalRelabelingHeuristic && (this.opsDone/2 % this.fn.n == this.fn.n-1))	// assume constant 2 for BFS
					this.globalRelabelingHeuristic();
			}
//			System.out.println(this.opsDone+" relabelings.");
			return this.e[this.t]; // this excess is the maximum flow value.
		}
		
		
		public boolean maxFlowKowalik() {
			int src = this.fn.n-2;
//		    System.out.println("Ignore stopping criterion for blocking flows: This is a push-relabel algorithm.");
		    long flow = this.maxFlow(src, this.fn.n-1);
		    
		    long capSourceArcs = 0;	// the value of the cut ({s}, V\{s})
		    for (final int c : this.fn.cap[src]) {
		    	capSourceArcs += c;
		    }
//		    System.out.println("Flow is "+flow+", source cut cap: "+capSourceArcs);
		    if (flow == capSourceArcs)
		    	return true;
		    return false;
		}
		
		
		public int flow(final int u, final int vPosInU) {
			return this.f[u][vPosInU];
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
	}
	
	public OneWayInOneClassPushRelabel(FlowNetwork fn, int[] indegrees) {
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
		PushRelabel fa = new PushRelabel(fn);
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
				ad[u].add(Integer.valueOf(v));
				ad[v].add(Integer.valueOf(u));
			}
			br.close();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for reading the graph.");
			start = System.currentTimeMillis();
			for (ArrayList<Integer> al : ad) {
				Collections.sort(al);	// for later use
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
			OneWayInOneClassPushRelabel ow = new OneWayInOneClassPushRelabel(fn, indegrees);
//			System.out.println("Start the search.");
//			int orientationNumber = ow.orientationNumberBinarySearch();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for reading the graph.");
			start = System.currentTimeMillis();
//			int orientationNumber = ow.orientationNumberLinearSearch();
			int orientationNumber = ow.orientationNumberBinarySearch();
			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for computing the orientation number:");
			System.out.println(orientationNumber);
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
