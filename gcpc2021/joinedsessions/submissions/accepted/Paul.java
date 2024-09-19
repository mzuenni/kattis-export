import java.util.*;
import java.io.*;

public class Paul {
	BufferedReader br;
	StringTokenizer st;

	int readInt() throws Exception {
		while (!st.hasMoreTokens()) {
			st = new StringTokenizer(br.readLine());
		}
		return Integer.valueOf(st.nextToken());
	}
	
	class Pair implements Comparable<Pair> {
		int a, b;

		Pair(int a, int b) {
			this.a = a;
			this.b = b;
		}

		public int compareTo(Pair p) {
			if (a != p.a) return Integer.compare(a,p.a);
			return Integer.compare(b,p.b);
		}
	}

	final int K = 5;

	void run() throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		
		int n = readInt();

		Pair[] intervals = new Pair[n];
		for (int i = 0; i < n; i++) {
			int a = readInt();
			int b = readInt();
			intervals[i] = new Pair(a,b);
		}
		Arrays.sort(intervals);
		
		Pair[] events = new Pair[2*n];
		for (int i = 0; i < n; i++) {
			events[2*i]   = new Pair(intervals[i].a, ~i);
			events[2*i+1] = new Pair(intervals[i].b, i);
		}
		Arrays.sort(events);

		int[] f = new int[n];
		int[] g = new int[n];

		TreeSet<Integer> active = new TreeSet<>();
		TreeSet<Integer> inactive = new TreeSet<>();
		for (var e: events) {
			int i = e.b;
			if (i < 0) {
				i = ~i;
				active.add(i);
				f[i] = active.first();
				g[i] = inactive.isEmpty() ? -1 : inactive.last();
			} else {
				active.remove(i);
				inactive.add(i);
			}
		}
		
		int[][] dp = new int[n+1][K];
		for (int[] row: dp) Arrays.fill(row, n+1);
		dp[0][0] = 0;

		for (int i = 0; i < n; i++) {
			int j = i, k = i;
			for (int ec = 0; ec < K; ec++) {
				j = f[j]; k = g[j];
				for (int c = ec; c < K; c++) {
					dp[i+1][c] = Math.min(dp[i+1][c], dp[k+1][c-ec] + 1);
				}
			}
		}
		
		if (dp[n][0] > dp[n][K-1]) {
			int c = 1;
			while (dp[n][c] == dp[n][0]) c++;
			System.out.println(c);
		} else {
			System.out.println("impossible");
		}
	}

	public static void main(String[] args) throws Exception {
		new Paul().run();
	}
}
