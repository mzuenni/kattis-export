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
public class PlugItIn_Markus_Dinitz_seminaiv {	
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
			Dinitz alg = new Dinitz(fn);
			
			
			long initialFlow = alg.maxFlow(source, target);
			if (initialFlow == n)	// all devices are connected.
				System.out.println(initialFlow);
			else {
				// which socket gets the plug board?
				long max = 0;
				for (int i = n; i < n+m; i++) {
					capL[i][0] = 3;	// note that fn does not use a copy
					alg.clearFlow();
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
