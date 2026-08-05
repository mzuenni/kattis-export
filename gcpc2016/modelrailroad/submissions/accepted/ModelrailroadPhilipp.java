import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.PriorityQueue;


public class ModelrailroadPhilipp {
	private static int mst(ArrayList<LinkedList<Edge>> edges) {
		HashSet<Integer> used = new HashSet<Integer>();
		PriorityQueue<Edge> queue = new PriorityQueue<>();
		used.add(0);
		for (Edge e : edges.get(0)) {
			queue.add(e);
		}
		int size = 0;
		while (used.size() != edges.size()) {
			if (queue.isEmpty()) {
				return -1;
			}
			Edge edge = queue.poll();
			while (used.contains(edge.end)) {
				if (queue.isEmpty()) {
					return -1;
				}
				edge = queue.poll();
			}
			size += edge.dist;
			used.add(edge.end);
			for (Edge e : edges.get(edge.end)) {
				if (!used.contains(e.end)) {
					queue.add(e);
				}
			}
		}
		return size;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] line = br.readLine().split(" ");
		int n = Integer.parseInt(line[0]);
		int m = Integer.parseInt(line[1]);
		int l = Integer.parseInt(line[2]);
		int sum = 0;
		ArrayList<LinkedList<Edge>> edges = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			edges.add(new LinkedList<Edge>());
		}
		for (int i = 0; i < m; i++) {
			line = br.readLine().split(" ");
			int a = Integer.parseInt(line[0]) - 1;
			int b = Integer.parseInt(line[1]) - 1;
			int c = Integer.parseInt(line[2]);
			if (i < l) {
				sum += c;
			}
			edges.get(a).add(new Edge(a,b,c));
			edges.get(b).add(new Edge(b,a,c));
		}
		int mst = mst(edges);
		if (mst >= 0 && mst <= sum) {
			System.out.println("possible");
		} else {
			System.out.println("impossible");
		}
	}
	
	static class Edge implements Comparable<Edge> {
		int start;
		int end;
		int dist;

		Edge(int start, int end, int dist) {
			this.start = start;
			this.end = end;
			this.dist = dist;
		}

		@Override
		public int compareTo(Edge o) {
			return dist - o.dist;
		}
		
		@Override
		public String toString() {
			return start + "<->" + end + ":"  + dist;
		}
	}

}
