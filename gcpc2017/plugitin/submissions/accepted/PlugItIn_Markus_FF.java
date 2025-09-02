import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;


/**
 * GCPC 2017 task.
 * @author mablumen
 *
 */
public class PlugItIn_Markus_FF {	
	static class FordFulkerson {
		final boolean[] visited;
		protected long maxFlow = 0;
		protected final FlowNetwork fn;
		protected int[][] f;
	  
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
					
					int df = dfs(v, t, Math.min(min, diff));
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
	}
	
	static int[][] convertToArray(ArrayList<Integer>[] al) {
		int[][] arr = new int[al.length][];
		for (int i = 0; i < al.length; i++) {
			arr[i] = convertToArray(al[i]);
		}
		return arr;
	}
	
	static int[] convertToArray(ArrayList<Integer> al) {
		int[] arr = new int[al.size()];
		for (int i = 0; i < al.size(); i++) {
			arr[i] = al.get(i).intValue();
		}
		return arr;
	}
	
	static int[][] deepCpy(int[][] arr) {
		int[][] cpy = new int[arr.length][];
		for (int i = 0; i < arr.length; i++) {
			cpy[i] = arr[i].clone();
		}
		return cpy;
	}
	
	public static void main(String[] args) {
		BufferedReader bf = new BufferedReader(new InputStreamReader(System.in));
		try {
			String line = bf.readLine();
			String[] split = line.split(" ");
			int m = Integer.parseInt(split[0]);
			int n = Integer.parseInt(split[1]);
			int k = Integer.parseInt(split[2]);
			int source = n+m;
			int target = n+m+1;
			ArrayList<Integer>[] adj = new ArrayList[n+m+2];	// for all nodes, one for s, one for t, one for the plugbar.
			ArrayList<Integer>[] posInAdj = new ArrayList[n+m+2];
			ArrayList<Integer>[] cap = new ArrayList[n+m+2];
			for (int i = 0; i < n+m+2; i++) {
				adj[i] = new ArrayList<>();
				posInAdj[i] = new ArrayList<>();
				cap[i] = new ArrayList<>();
			}
			final Integer ONE = Integer.valueOf(1);
			final Integer ZERO = Integer.valueOf(0);
			
			for (int i = 0; i < n; i++) {
				adj[i].add(source);
				cap[i].add(ZERO);
				adj[source].add(Integer.valueOf(i));	// source arcs
				cap[source].add(ONE);
				posInAdj[source].add(ZERO);
				posInAdj[i].add(Integer.valueOf(i));
			}
			for (int i = n; i < n+m; i++) {	
				adj[i].add(target);
				cap[i].add(ONE);						// sink arcs
				adj[target].add(Integer.valueOf(i));
				cap[target].add(ZERO);
				posInAdj[target].add(ONE);
				posInAdj[i].add(Integer.valueOf(i)-n);
			}			
			for (int i = 0; i < k; i++) {
				line = bf.readLine();
				split = line.split(" ");
				int u = Integer.parseInt(split[1])-1;	// device
				int v = Integer.parseInt(split[0])+n-1;	// socket
				adj[u].add(Integer.valueOf(v));
				adj[v].add(Integer.valueOf(u));
				cap[u].add(ONE);
				cap[v].add(ZERO);
				posInAdj[u].add(Integer.valueOf(adj[v].size()-1));
				posInAdj[v].add(Integer.valueOf(adj[u].size()-1));
			}
			
			int[][] adjL = convertToArray(adj);
			int[][] revPos = convertToArray(posInAdj);
			int[][] capL = convertToArray(cap);
			
			FlowNetwork fn = new FlowNetwork(adjL, revPos, capL);
			FordFulkerson alg = new FordFulkerson(fn);
			
			
			long initialFlow = alg.maxFlow(source, target);
			int[][] initialF = alg.f;
			
			if (initialFlow == n)	// all devices are connected.
				System.out.println(initialFlow);
			else {
				// which socket gets the plug board?
				long max = 0;
				for (int i = n; i < n+m; i++) {
					capL[i][0] = 3;	// note that fn does not use a copy
					
					alg.maxFlow = initialFlow;
					alg.f = deepCpy(initialF);
					long flow = alg.maxFlow(source, target);
					if (flow > max)
						max = flow;
					if (flow == n || (flow == initialFlow+2))
						break;
					capL[i][0] = 1;	// reset
				}
				System.out.println(max);
			}
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
