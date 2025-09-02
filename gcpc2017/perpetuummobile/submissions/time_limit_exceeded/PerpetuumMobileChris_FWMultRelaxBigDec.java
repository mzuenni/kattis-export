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
import java.util.Map.Entry;
import java.util.StringTokenizer;

public class PerpetuumMobileChris_FWMultRelaxBigDec {

	static boolean fw_mult(ArrayList<HashMap<Integer, Double>> graph) {

		int n = graph.size();
		BigDecimal[][] dist = new BigDecimal[n][n];

		for (int i = 0; i < n; i++) {
			dist[i][i] = BigDecimal.ZERO;
			for (Entry<Integer, Double> e : graph.get(i).entrySet()) {
				dist[i][e.getKey()] = BigDecimal.valueOf(e.getValue());
			}
		}

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (dist[i][k] != null && dist[k][j] != null) {
						// path from i to j via k
						BigDecimal alt = dist[i][k].multiply(dist[k][j]);
						if (dist[i][j] == null || dist[i][j].compareTo(alt) < 0) { // note the *
							dist[i][j] = alt;
						}
						if (i == j && dist[i][j].compareTo(BigDecimal.ONE) >= 1) {
							return true;
						}
					}
				}
			}
		}

		return false;
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

		boolean negcycle = fw_mult(graph);

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
