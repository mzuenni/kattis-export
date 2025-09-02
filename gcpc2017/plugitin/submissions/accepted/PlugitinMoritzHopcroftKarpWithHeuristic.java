import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.StringTokenizer;

public class PlugitinMoritzHopcroftKarpWithHeuristic {

	static int reset = 0;
	
  static class Edge {
    int t, rev, cap, f, rec;
    int resetHandled;

    public Edge(int t, int rev, int cap) {
      this.t = t;
      this.rev = rev;
      this.cap = cap;
      this.resetHandled = reset;
    }
    
    public int getF() {
    	updateF();
    	return this.f;
    }
    
    private void updateF() {
    	if (this.resetHandled != reset) {
    		this.f = this.rec;
    		this.resetHandled = reset;
    	}
    }
    
    public void addF(int add) {
    	updateF();
    	this.f += add;
    }
  }
  
  public static void saveFlow(List<Edge>[] graph) {
	  for (List<Edge> l :graph) {
		  for (Edge e : l) {
			  e.rec = e.f;
		  }
	  }
  }
  
  public static void recoverFlow(List<Edge>[] graph) {
	  for (List<Edge> l :graph) {
		  for (Edge e : l) {
			  e.f = e.rec;
		  }
	  }
  }
  
  public static List<Edge>[] createGraph(int nodes) {
    List<Edge>[] graph = new List[nodes];
    for (int i = 0; i < nodes; i++)
      graph[i] = new ArrayList<>();
    return graph;
  }

  public static void addEdge(List<Edge>[] graph, int s, int t, int cap) {
    graph[s].add(new Edge(t, graph[t].size(), cap));
    graph[t].add(new Edge(s, graph[s].size() - 1, 0));
  }

  static boolean dinicBfs(List<Edge>[] graph, int src, int dest, int[] dist) {
    Arrays.fill(dist, -1);
    dist[src] = 0;
    int[] Q = new int[graph.length];
    int sizeQ = 0;
    Q[sizeQ++] = src;
    for (int i = 0; i < sizeQ; i++) {
      int u = Q[i];
      for (Edge e : graph[u]) {
        if (dist[e.t] < 0 && e.getF() < e.cap) {
          dist[e.t] = dist[u] + 1;
          Q[sizeQ++] = e.t;
        }
      }
    }
    return dist[dest] >= 0;
  }

  static int dinicDfs(List<Edge>[] graph, int[] ptr, int[] dist, int dest, int u, int f) {
    if (u == dest)
      return f;
    for (; ptr[u] < graph[u].size(); ++ptr[u]) {
      Edge e = graph[u].get(ptr[u]);
      if (dist[e.t] == dist[u] + 1 && e.getF() < e.cap) {
        int df = dinicDfs(graph, ptr, dist, dest, e.t, Math.min(f, e.cap - e.getF()));
        if (df > 0) {
          e.addF(df);
          graph[e.t].get(e.rev).addF(-df);
          return df;
        }
      }
    }
    return 0;
  }

  public static int maxFlow(List<Edge>[] graph, int src, int dest) {
    int flow = 0;
    int[] dist = new int[graph.length];
    while (dinicBfs(graph, src, dest, dist)) {
      int[] ptr = new int[graph.length];
      while (true) {
        int df = dinicDfs(graph, ptr, dist, dest, src, Integer.MAX_VALUE);
        if (df == 0)
          break;
        flow += df;
      }
    }
    return flow;
  }

  public static void main(String[] args) throws IOException {
	Reader reader = new Reader();
	reader.init();
	int m = reader.nextInt();
	int n = reader.nextInt();
	int k = reader.nextInt();
	  
	List<Edge>[] graph = createGraph(m+n+3);
    int source = 0;
    int sink = n+m+1;
    Set<Integer> connectable = new HashSet<>();
	for(int i=0;i<k;i++) {
		int from = reader.nextInt();
		int to = reader.nextInt();
		
		connectable.add(to);
		addEdge(graph, from, to+m, 1);
	}
	
	for(int i=1;i<=m;i++) {
		addEdge(graph, source, i, 1);
	}
	for(int i=m+1;i<=n+m;i++) {
		addEdge(graph, i, sink, 1);
	}
	
	int mf = maxFlow(graph, source, sink);
	
	int add = Math.min(2, n-mf);
	
	saveFlow(graph);
	
	int res = mf;
	if (add > 0) {
		for(int i=1; i<=m; i++) {
			// This socket was used, hence tripling it might make sense.
			if (graph[0].get(i-1).getF() == 1) {
				//start = System.currentTimeMillis();
				graph[0].get(i-1).cap += add;
				
				int mf2 = maxFlow(graph, source, sink);
				res = Math.max(res, mf + mf2);			
				
				if (res >= mf+2 || res == connectable.size()) {
					break;
				}
				
				graph[0].get(i-1).cap -= add;
				//recoverFlow(graph);
				
				reset++;
				//end = System.currentTimeMillis();
				//System.out.println(end-start);
			}
		}
	}
	
	System.out.println(res);
	
  }

  static class Reader {
	    static BufferedReader reader;
	    static StringTokenizer tokenizer;

	    static void init() {
	        reader = new BufferedReader(
	                     new InputStreamReader(System.in) );
	        tokenizer = new StringTokenizer("");
	    }

	    static String next() throws IOException {
	        while ( ! tokenizer.hasMoreTokens() ) {
	            tokenizer = new StringTokenizer(
	                   reader.readLine() );
	        }
	        return tokenizer.nextToken();
	    }

	    static int nextInt() throws IOException {
	        return Integer.parseInt( next() );
	    }
	}
  
}

