import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen_overflow {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	static int n, m;
	static TreeSet<Edge>[] nbs;
	static List<Integer>[] bridges;
	static int[] a, b;
	static boolean[] odd, seen, seen_bridge;

	public static void main(String[] args) throws Exception {
		// Read input
		n = Integer.valueOf(in.readLine());
		nbs = new TreeSet[n];
		bridges = new List[n];
		for(int i = 0; i < n; i++) {
			nbs[i] = new TreeSet<Edge>();
			bridges[i] = new ArrayList<Integer>();
		}
		for(int i = 0; i < n - 1; i++) {
			String[] ps = in.readLine().split(" ");
			int a = Integer.valueOf(ps[0]);
			int b = Integer.valueOf(ps[1]);
			int w = Integer.valueOf(ps[2]);
			nbs[a-1].add(new Edge(b-1, w));
			nbs[b-1].add(new Edge(a-1, w));
		}
		
		m = Integer.valueOf(in.readLine());
		a = new int[m];
		b = new int[m];
		for(int i = 0; i < m; i++) {
			String[] ps = in.readLine().split(" ");
			a[i] = Integer.valueOf(ps[0]) - 1;
			b[i] = Integer.valueOf(ps[1]) - 1;
			bridges[a[i]].add(i);
			bridges[b[i]].add(i);
		}

		// Pick 0 as root and process nodes in in a post order
		odd = new boolean[n];
		process(0, -1);

		// Now a tour is possible iff the graph is fully connected
		seen = new boolean[n];
		seen_bridge = new boolean[m];
		visit(a[0]); // start in any node with a bridge
		for(int i = 0; i < m; i++) {
			if(!seen_bridge[i]) {
				System.out.println("impossible");
				return;
			}
		}

		// Connected, so each remaining edge must be used once
		int answer = 0;
		for(int i = 0; i < n; i++) {
			for(Edge e : nbs[i]) {
				answer += e.w;
			}
		}
		System.out.println(answer / 2); // we counted everything twice
	}

	static boolean process(int i, int parent) {
		// First visit all children
		ArrayList<Edge> to_remove = new ArrayList<Edge>();
		for(Edge e : nbs[i]) {
			if(e.to == parent) continue;
			if(process(e.to, i)) to_remove.add(e);
		}
		nbs[i].removeAll(to_remove);
		for(Edge e : to_remove)
			nbs[e.to].remove(new Edge(i, e.w));

		// Nothing else to do for the root
		if(parent == -1) return false;

		// Then handle this node. We check whether an odd
		// or even number of bridges is connected to this
		// subgraph.
		odd[i] = bridges[i].size() % 2 != 0;
		for(Edge e : nbs[i]) {
			if(e.to == parent) continue;
			odd[i] ^= odd[e.to];
		}

		// If it is odd, this edge must be used for a tour,
		// otherwise it either is not needed, or is needed
		// twice (which is forbidden), so in that case we
		// remove the edge to the parent
		return !odd[i];
	}

	// dfs style visit all non-visited nodes, following
	// tree edges and bridges
	static void visit(int i) {
		if(seen[i]) return;
		seen[i] = true;

		for(Edge e : nbs[i])
			visit(e.to);

		for(int j : bridges[i]) {
			seen_bridge[j] = true;
			visit(a[j] == i ? b[j] : a[j]);
		}
	}
}

class Edge implements Comparable<Edge> {
	public int to, w;

	public Edge(int to, int w) {
		this.to = to;
		this.w = w;
	}

	public int compareTo(Edge other) {
		return to - other.to;
	}
}
