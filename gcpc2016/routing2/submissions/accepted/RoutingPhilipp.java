
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class RoutingPhilipp {
	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		int n = sc.nextInt();
		ArrayList<HashMap<Integer, HashSet<Integer>>> servers = new ArrayList<>();
		int[] processing = new int[n];
		for (int i = 0; i < n; i++) {
			HashMap<Integer,HashSet<Integer>> server = new HashMap<>();
			servers.add(server);
			int m = sc.nextInt();
			processing[i] = sc.nextInt();
			for (int j = 0; j < m; j++) {
				int count = sc.nextInt();
				int tar = sc.nextInt()-1;
				HashSet<Integer> except = new HashSet<>();
				for (int k = 0; k < count; k++) {
					except.add(sc.nextInt()-1);
				}
				server.put(tar, except);
			}
		}
		int min = dijkstra(servers, processing);
		if (min == Integer.MAX_VALUE) {
			System.out.println("impossible");
		} else {
			System.out.println(min+processing[n-1]);
		}
	}
	
	public static int dijkstra(ArrayList<HashMap<Integer, HashSet<Integer>>> servers, int[] processing) {
		PriorityQueue<Node> dijQueue = new PriorityQueue<>();
		int[][] dist = new int[processing.length][processing.length];
		boolean[][] finished = new boolean[processing.length][processing.length];
		for (int i = 0; i < dist.length; i++) {
			Arrays.fill(dist[i], Integer.MAX_VALUE);
		}
		dist[0][0] = 0;
		dijQueue.add(new Node(0,0,0));
		while (!dijQueue.isEmpty()) {
			Node p = dijQueue.poll();
			if (finished[p.server][p.prev]) {
				continue;
			}
			finished[p.server][p.prev] = true;
			if (p.server == processing.length-1) {
				return p.dist;
			}
			HashMap<Integer, HashSet<Integer>> server = servers.get(p.server);
			for (int tar : server.keySet()) {
				if (server.get(tar).contains(p.prev)) {
					continue;
				}
				if (!finished[tar][p.server]) {
					if (p.dist + processing[p.server] < dist[tar][p.server]) {
						dist[tar][p.server] = p.dist + processing[p.server];
						dijQueue.add(new Node(tar,p.server,dist[tar][p.server]));
					}
				}
			}
		}
		return Integer.MAX_VALUE;
	}

	private static class Node implements Comparable<Node> {
		int server;
		int prev;
		int dist;

		Node(int server, int prev, int dist) {
			this.server = server;
			this.prev = prev;
			this.dist = dist;
		}

		@Override
		public int compareTo(Node o) {
			return dist - o.dist;
		}
	}


	static class FastScanner {
		BufferedReader br = null;
		StringTokenizer st = null;
	
		FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(System.in));
		}
	
		public String next() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}
	
		public int nextInt() {
			return Integer.parseInt(next());
		}
		public double nextDouble() {
			return Double.parseDouble(next());
		}
	}
}
