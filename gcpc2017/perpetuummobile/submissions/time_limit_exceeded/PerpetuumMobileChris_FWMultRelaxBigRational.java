import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.StringTokenizer;

public class PerpetuumMobileChris_FWMultRelaxBigRational {

	static boolean fw_mult(ArrayList<HashMap<Integer, Rational>> graph) {

		int n = graph.size();
		Rational[][] dist = new Rational[n][n];

		for (int i = 0; i < n; i++) {
			dist[i][i] = Rational.ZERO;
			for (Entry<Integer, Rational> e : graph.get(i).entrySet()) {
				dist[i][e.getKey()] = e.getValue();
			}
		}

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (dist[i][k] != null && dist[k][j] != null) {
						// path from i to j via k
						Rational alt = dist[i][k].multiply(dist[k][j]);
						if (dist[i][j] == null || dist[i][j].compareTo(alt) < 0) { // note the *
							dist[i][j] = alt;
						}
						if (i == j && dist[i][j].compareTo(Rational.ONE) >= 1) {
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

		ArrayList<HashMap<Integer, Rational>> graph = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			graph.add(new HashMap<>());
		}

		for (int i = 0; i < m; i++) {
			int ai = sc.nextInt() - 1;
			int bi = sc.nextInt() - 1;
			Rational ci = Rational.valueOf(sc.next());

			HashMap<Integer, Rational> out = graph.get(ai);
			if (out.containsKey(bi)) {
				Rational old = out.get(bi);
				if (ci.compareTo(old) >= 1) {
					out.put(bi, old);
				}
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
	
	static class Rational implements Comparable<Rational> {
		public static final Rational ONE = new Rational(1);
		public static final Rational ZERO = new Rational(0);
		private BigInteger a,b;
		
		public Rational(BigInteger a, BigInteger b) {
			this.a = a;
			this.b = b;
			this.simplify();
		}
		
		public Rational(long r, long q) {
			this(BigInteger.valueOf(r),BigInteger.valueOf(q));
		}
		
		public Rational(long l) {
			this(l,1);
		}
		
		private void simplify() {
			if (a.equals(BigInteger.ZERO)) {
				b = BigInteger.ONE;
			} else {
				BigInteger gcd = a.gcd(b);
				a = a.divide(gcd);
				b = b.divide(gcd);
			}
			if (a.signum() == -1 && b.signum() == -1) {
				a = a.abs();
				b = b.abs();
			}
		}
		
		public Rational add(Rational r) {
			Rational q = new Rational(a.multiply(r.b).add(b.multiply(r.a)),b.multiply(r.b));
			q.simplify();
			return q;
		}
		
		public Rational multiply(Rational r) {
			Rational q = new Rational(a.multiply(r.a),b.multiply(r.b));
			q.simplify();
			return q;
		}
		
		public Rational divide(Rational r) {
			Rational q = new Rational(r.b,r.a);
			return multiply(q);
		}
		
		public Rational subtract(Rational r) {
			Rational q = new Rational(r.a.negate(),r.b);
			return add(q);
		}
		
		public Rational toThePowerOf(long n) {
			if(n == 1) {
				return this;
			}
			else {
				Rational r = multiply(this).toThePowerOf(n/2);
				if(n % 2 == 1) {
					r = r.multiply(this);
				}
				return r;
			}
		}
		
		@Override
		public int compareTo(Rational arg) {
			return a.multiply(arg.b).subtract(b.multiply(arg.a)).compareTo(BigInteger.ZERO);
		}
		
		public String toString() {
			simplify();
			return a.toString()+"/"+b.toString();
		}
		
		public static Rational valueOf(String d) {
			if (!d.contains(".")) {
				return new Rational(Long.parseLong(d));
			}
		    long wholes = Long.parseLong(d.substring(0, d.indexOf(".")));
		    String fracpart = d.substring(d.indexOf(".") + 1);
		    long fracs = Long.parseLong(fracpart);
		    long fraclength = fracpart.length();
		    
		    Rational f = new Rational(fracs, (long) Math.pow(10, fraclength));
		    return f.add(new Rational(wholes));
		}
	}

}
