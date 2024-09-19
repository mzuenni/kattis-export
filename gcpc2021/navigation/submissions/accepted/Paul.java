import java.util.*;
import java.io.*;

public class Paul {
	final long INF = (long) 1e16;

	class Node {
		Map<Integer,Integer> outdeg;
		List<Edge> incoming;
		long distance = INF;

		void addOutgoing(int color) {
			outdeg.compute(color, (k,v) -> (v == null) ? 1 : v+1);
		}

		void addIncoming(Node comeFrom, int color, int length) {
			incoming.add(new Edge(comeFrom, color, length));
		}

		public Node() {
			this.outdeg = new HashMap<>();
			this.incoming = new ArrayList<>();
		}
	}

	class Edge {
		Node comeFrom;
		int color, length;

		public Edge(Node comeFrom, int color, int length) {
			this.comeFrom = comeFrom;
			this.color = color;
			this.length = length;
		}
	}

	class QueueEntry implements Comparable<QueueEntry> {
		Node node;
		int color;
		long distance;

		void process(PriorityQueue<QueueEntry> pq) {
			if (color > 0) {
				if (node.outdeg.compute(color, (k,v) -> v-1) > 0) return;
				if (distance >= node.distance) return;
			}

			node.distance = distance;

			for (Edge e: node.incoming) {
				pq.add(new QueueEntry(e.comeFrom, e.color, distance + e.length));
			}
		}

		public QueueEntry(Node node, int color, long distance) {
			this.node = node;
			this.color = color;
			this.distance = distance;
		}

		public int compareTo(QueueEntry q) {
			if (distance != q.distance) return Long.compare(distance, q.distance);
			return Integer.compare(this.hashCode(), q.hashCode());
		}
	}

	void run() throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		String[] nums = br.readLine().split(" ");
		int n = Integer.valueOf(nums[0]);
		int m = Integer.valueOf(nums[1]);
		int k = Integer.valueOf(nums[2]);

		Node[] nodes = new Node[n];
		for (int i = 0; i < n; i++) {
			nodes[i] = new Node();
		}
		
		while (m --> 0) {
			String[] fst = br.readLine().split(" ");
			String[] snd = br.readLine().split(" ");
			
			int a = Integer.valueOf(fst[0]) - 1;
			int b = Integer.valueOf(fst[1]) - 1;
			int length = Integer.valueOf(fst[2]);

			for (int i = 1; i < snd.length; i++) {
				int color = Integer.valueOf(snd[i]);
				nodes[a].addOutgoing(color);
				nodes[b].addIncoming(nodes[a], color, length);
			}
		}

		PriorityQueue<QueueEntry> pq = new PriorityQueue<>();
		pq.add(new QueueEntry(nodes[n-1], -1, 0));
		
		while (!pq.isEmpty()) {
			pq.poll().process(pq);
		}

		if (nodes[0].distance < INF) {
			System.out.println(nodes[0].distance);
		} else {
			System.out.println("impossible");
		}
	}

	public static void main(String[] args) throws Exception {
		new Paul().run();
	}
}
