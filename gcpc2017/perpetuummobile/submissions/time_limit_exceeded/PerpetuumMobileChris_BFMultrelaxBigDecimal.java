import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.StringTokenizer;

public class PerpetuumMobileChris_BFMultrelaxBigDecimal {

	private static boolean bellman_ford_mult(int start, ArrayList<HashMap<Integer, Double>> graph, int n) {
		
		BigDecimal[] dist = new BigDecimal[n];
		boolean[] inQueue = new boolean[n];
		Queue<Integer> queue = new LinkedList<Integer>();
		
		// initialization
		dist[start] = BigDecimal.ONE;
				
		// Bellman-Ford
		queue.add(start); // put task 0 in queue
		inQueue[start] = true;
		int counter = 0;
		while (!queue.isEmpty() && counter++ <= n) {
			int queueSize = queue.size();
			for (int q=1; q<=queueSize; q++) {
				int v = queue.poll();
				inQueue[v] = false;
				for (Entry<Integer, Double> e : graph.get(v).entrySet()) {
					int w = e.getKey();
					double c = e.getValue();
					
					BigDecimal alt = dist[v].multiply(BigDecimal.valueOf(c));
					
					if (dist[w] == null || dist[w].compareTo(alt) < 0) {
						dist[w] = alt;
						
						if (dist[start].compareTo(BigDecimal.ONE) >= 1) {
							return true;
						}
						
						if (!inQueue[w]) {
							queue.add(w);
							inQueue[w] = true;
						}
					}
				}
			}
		}
		
		return !queue.isEmpty();
	}

	public static void main(String[] args) throws IOException {

		FastScanner sc = new FastScanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		ArrayList<HashMap<Integer, Double>> graph = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			graph.add(new HashMap<>());
		}

		for (int i = 0; i < m; i++) {
			int ai = sc.nextInt() - 1;
			int bi = sc.nextInt() - 1;
			double ci = sc.nextDouble();

			HashMap<Integer, Double> out = graph.get(ai);
			if (out.containsKey(bi)) {
				double old = out.get(bi);
				out.put(bi, Math.max(ci, old));
			} else {
				out.put(bi, ci);
			}
		}

		boolean negcycle = false;
		for (int i = 0; i < n; i++) {
			negcycle |= bellman_ford_mult(i, graph, n);
			if (negcycle) { break; }
		}

		if (negcycle) {
			System.out.println("inadmissible");
		} else {
			System.out.println("admissible");
		}

		sc.close();
	}

	static class FastScanner implements AutoCloseable {
		BufferedReader br = null;
		StringTokenizer st = null;

		FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(in));
		}

		FastScanner(File in) throws FileNotFoundException {
			br = new BufferedReader(new FileReader(in));
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

		public long nextLong() {
			return Long.parseLong(next());
		}

		public double nextDouble() {
			return Double.parseDouble(next());
		}

		@Override
		public void close() throws IOException {
			br.close();
		}
	}
}
