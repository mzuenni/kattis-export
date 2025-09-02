import java.util.*;
import java.math.*;

public class CheckCycles {
	
	static final BigDecimal wMin = new BigDecimal("0.0001"), wMax = new BigDecimal("5.0");
	static final BigDecimal cMin = new BigDecimal("0.9"), cMax = new BigDecimal("1.1");

	static class Edge {
		int to;
		BigDecimal weight;
		
		public Edge(int to, BigDecimal weight) {
			this.to = to;
			this.weight = weight;
		}
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt(), m = sc.nextInt();
		
		List<Edge>[] adj = new ArrayList[n];
		for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
		
		boolean[][] reach = new boolean[n][n];
		for (int i = 0; i < n; i++) reach[i][i] = true;

		while (m --> 0) {
			int a = sc.nextInt()-1;
			int b = sc.nextInt()-1;
			BigDecimal weight = new BigDecimal(sc.next());
			if (weight.compareTo(wMin) < 0 || weight.compareTo(wMax) > 0 || weight.scale() > 4) {
				System.out.println("Invalid edge weight: " + weight);
				System.out.println(a + " " + b);
				System.exit(43);
			}
			adj[a].add(new Edge(b,weight));
			reach[a][b] = true;
		}
		
		System.out.println("All edges OK!");
		
		for (int k = 0; k < n; k++) 
			for (int i = 0; i < n; i++) 
				for (int j = 0; j < n; j++)
					if (reach[i][k] && reach[k][j]) reach[i][j] = true;
		
		// find SCCs
		int C = 0;
		int[] comp = new int[n];
		Arrays.fill(comp,-1);
		List<Integer> roots = new ArrayList();
		for (int i = 0; i < n; i++) {
			if (comp[i] != -1) continue;
			
			for (int j = 0; j < n; j++) if (reach[i][j] && reach[j][i]) comp[j] = C;
			roots.add(i);
			C++;
		}
		
		System.out.println(C);
		
		boolean allCyclesOK = true;

		// run Bellman-Ford in every SCC
		for (int c = 0; c < C; c++) {
			int s = roots.get(c);
			System.out.println(s);

			BigDecimal[] dist = new BigDecimal[n];
			for (Edge e: adj[s]) if (comp[e.to] == c) {
				if (dist[e.to] == null || e.weight.compareTo(dist[e.to]) > 0)
					dist[e.to] = e.weight;
			}
	
			for (int t = 0; t < n; t++) {
				boolean done = true;
				BigDecimal[] nDist = new BigDecimal[n];
				for (int i = 0; i < n; i++) nDist[i] = dist[i];
				
				for (int i = 0; i < n; i++) if (comp[i] == c) {
					if (dist[i] == null) continue;
					
					for (Edge e: adj[i]) if (comp[e.to] == c) {
						BigDecimal x = dist[i].multiply(e.weight);
						if (nDist[e.to] == null || nDist[e.to].compareTo(x) < 0) {
							nDist[e.to] = x;
							done = false;
						}
					}
				}
				dist = nDist;
				// found a cycle of product >= cMax
				if (dist[s] != null && dist[s].compareTo(cMax) >= 0) System.exit(42);
				if (done) break;
			}
			// found a cycle of product > cMin
			// need to find a cycle of product >= cMax elsewhere now
			if (dist[s] != null && dist[s].compareTo(cMin) > 0) allCyclesOK = false;
		}
		System.exit(allCyclesOK ? 42 : 43);
	}
}
