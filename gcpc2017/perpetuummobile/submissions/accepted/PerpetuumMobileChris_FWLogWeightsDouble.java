import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.StringTokenizer;
import java.util.Arrays;

public class PerpetuumMobileChris_FWLogWeightsDouble {

	static boolean fw_mult(ArrayList<HashMap<Integer, Double>> graph) {

		int n = graph.size();
		double[][] dist = new double[n][n];
		
		for(int i=0;i<n;i++)
			Arrays.fill(dist[i], Double.NEGATIVE_INFINITY);
									
		for (int i = 0; i < n; i++) {
			dist[i][i] = 0.0;
			for (Entry<Integer, Double> e : graph.get(i).entrySet()) {
				dist[i][e.getKey()] = e.getValue();
			}
		}

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					// path from i to j via k
					if (dist[i][j] < dist[i][k] + dist[k][j]) { // note the +
						dist[i][j] = dist[i][k] + dist[k][j];
					}
					if (i == j && dist[i][j] > 0) {
						return true;
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
			double ci = Math.log(sc.nextDouble());

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
