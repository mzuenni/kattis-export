import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class PolyChris {

	static long area(int n, long[] x, long[] y) {
		long ret = 0;
		for (int i = 0; i < n; i++) {
			long d1 = x[i] * y[(i + 1) % n];
			ret += d1;
			long d2 = y[i] * x[(i + 1) % n];
			ret -= d2;
		}
		return Math.abs(ret);
	}

	static long gcd(long a, long b) {
		if (b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}

	public static void main(String[] args) throws IOException {
		FastScanner sc = new FastScanner(System.in);

		int n = sc.nextInt();

		long[] x = new long[n];
		long[] y = new long[n];
		for (int i = 0; i < n; i++) {
			x[i] = sc.nextLong();
			y[i] = sc.nextLong();
		}
		sc.close();

		long darea = area(n, x, y);

		long p = n;
		for (int i = 0; i < n; i++) {
			p += gcd(Math.abs(x[i] - x[(i + 1) % n]), Math.abs(y[i] - y[(i + 1) % n])) - 1;
		}

		long res = (long) ((darea - p) / 2.0) + 1;
		System.out.println(res);
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
