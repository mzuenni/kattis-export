import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;

public class OneWayMoritzDfsRandomOrientation {

	static Node[] nodes;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		nodes = new Node[n];
		for (int i = 0; i < n; i++) {
			nodes[i] = new Node(i);
		}

		for (int i = 0; i < m; i++) {
			int from = sc.nextInt()-1;
			int to = sc.nextInt()-1;

			// Pick orientation
			nodes[to].edges.add(new Edge(to, from));
		}

		PriorityQueue<Node> pq = new PriorityQueue<Node>();
		for (Node node : nodes) {
			pq.add(node);
		}

		while (!pq.isEmpty()) {
			Node node = pq.poll();
			int start_degree = node.edges.size();
			Stack<Edge> q = new Stack<Edge>();
			HashSet<Integer> done = new HashSet<Integer>();
			done.add(node.id);
			for (Edge e : node.edges) {
				q.add(e);
			}
			// System.out.println("Starting ata " + node.id);
			Set<Node> res = dfs(start_degree, new HashSet<Integer>(), node);
			// update
			if (res != null) {
				for (Node back : res) {
					pq.remove(back);
					pq.add(back);
				}
			}
		}

		int degree = 0;
		for (Node node : nodes) {
			degree = Math.max(node.edges.size(), degree);
		}
		System.out.println(degree);

	}

	public static Set<Node> dfs(int start_degree, Set<Integer> done,
			Node current) {

		if (start_degree - current.edges.size() >= 2) {
			Set<Node> ret = new HashSet<Node>();
			ret.add(current);
			// System.out.println("Stopping at " + current.id);
			return ret;
		}

		for (Edge e : current.edges) {
			if (!done.contains(e.to)) {

				done.add(e.to);
				Set<Node> ret = dfs(start_degree, done, nodes[e.to]);
				if (ret != null) {
					nodes[e.from].edges.remove(e);
					nodes[e.to].edges.add(new Edge(e.to, e.from));
					ret.add(current);
					return ret;
				}

			}
		}
		return null;
	}

	static class Node implements Comparable<Node> {
		List<Edge> edges;
		int id;

		public Node(int id) {
			this.id = id;
			edges = new LinkedList<Edge>();
		}

		@Override
		public int compareTo(Node n) {
			return -this.edges.size() + n.edges.size();
		}
	}

	static class Edge {
		int from, to;

		public Edge(int from, int to) {
			this.from = from;
			this.to = to;
		}
	}

}
