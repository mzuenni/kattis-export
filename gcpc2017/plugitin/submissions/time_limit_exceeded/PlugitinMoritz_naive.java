import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;



public class PlugitinMoritz_naive {

  static class Edge {
    int t, rev, cap, f;

    public Edge(int t, int rev, int cap) {
      this.t = t;
      this.rev = rev;
      this.cap = cap;
    }
  }
  
  public static void resetNetwork(List<Edge>[] graph) {
	  for (List<Edge> l :graph) {
		  for (Edge e : l) {
			  e.f = 0;
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
        if (dist[e.t] < 0 && e.f < e.cap) {
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
      if (dist[e.t] == dist[u] + 1 && e.f < e.cap) {
        int df = dinicDfs(graph, ptr, dist, dest, e.t, Math.min(f, e.cap - e.f));
        if (df > 0) {
          e.f += df;
          graph[e.t].get(e.rev).f -= df;
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

  public static void main(String[] args) {
	Scanner sc = new Scanner(System.in);
	int m = sc.nextInt();
	int n = sc.nextInt();
	int k = sc.nextInt();
	  
	List<Edge>[] graph = createGraph(m+n+3);
    int source = 0;
    int sink = n+m+1;
	for(int i=0;i<k;i++) {
		int from = sc.nextInt();
		int to = sc.nextInt();
		
		addEdge(graph, from, to+m, 1);
	}
	
	for(int i=1;i<=m;i++) {
		addEdge(graph, source, i, 1);
	}
	for(int i=m+1;i<=n+m;i++) {
		addEdge(graph, i, sink, 1);
	}
	
	int res = 0;
	for(int i=1; i<=m; i++) {
		// Triple the socket
		graph[0].get(i-1).cap += 2;
		res = Math.max(res, maxFlow(graph, source, sink));			
		graph[0].get(i-1).cap -= 2;

		resetNetwork(graph);
	}
	System.out.println(res);
	
  }
}