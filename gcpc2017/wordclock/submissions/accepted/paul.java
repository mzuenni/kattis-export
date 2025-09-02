import java.util.*;

class Pair implements Comparable<Pair> {
	int r, c;
	
	public Pair(int r, int c) {
		this.r = r;
		this.c = c;
	}

	public int compareTo(Pair other) {
		if (r == other.r)
			return Integer.compare(c, other.c);
		return Integer.compare(r, other.r);
	}
}

public class paul {
	static final int oo = (int) 1e6;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int height = sc.nextInt();
		int width = sc.nextInt();
		int n = sc.nextInt();

		String[] words = new String[n];
		for (int i = 0; i < n; i++) {
			words[i] = sc.next();
			if (words[i].length() > width) {
				System.out.println("impossible");
				return;
			}
		}

		// eliminate substrings
		int newN = 0;
		for (int i = 0; i < n; i++) {
			boolean ok = true;
			for (int j = 0; j < n; j++)
				if (i != j && words[j].indexOf(words[i]) != -1)
					ok = false;
			if (ok)
				words[newN++] = words[i];
		}
		n = newN;
		words = Arrays.copyOf(words, n);
		
		// find distances
		int[][] dist = new int[n][n];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				
				int li = words[i].length(), lj = words[j].length();

				for (int k = 0; k < Math.min(li, lj); k++)
					if (words[i].substring(li-k).equals(words[j].substring(0,k)))
						dist[i][j] = lj-k;
			}

		// travelling salesman DP
		Pair[][] dp = new Pair[1 << n][n];
		for (Pair[] row: dp)
			Arrays.fill(row, new Pair(oo,oo));
		int[][] pred = new int[1 << n][n];

		for (int i = 0; i < n; i++)
			dp[1 << i][i] = new Pair(0, words[i].length());

		for (int mask = 0; mask < (1 << n); mask++)
			for (int i = 0; i < n; i++) {
				if ((mask & (1 << i)) == 0)
					continue;
				for (int j = 0; j < n; j++) {
					if ((mask & (1 << j)) != 0)
						continue;
					Pair newVal = new Pair(dp[mask][i].r, dp[mask][i].c);
					newVal.c += dist[i][j];
					if (newVal.c > width) {
						newVal.c = words[j].length();
						newVal.r++;
					}
					if (newVal.compareTo(dp[mask | (1 << j)][j]) < 0) {
						dp[mask | (1 << j)][j] = newVal;
						pred[mask | (1 << j)][j] = i;
					}
				}
			}
		
		// reconstruct
		int mask = (1 << n) - 1, i = -1;
		for (int j = 0; j < n; j++)
			if (dp[mask][j].r < height)
				i = j;
		
		if (i == -1) {
			System.out.println("impossible");
			return;
		}
		
		char[][] res = new char[height][width];
		for (char[] row: res)
			Arrays.fill(row, 'Q');
		
		while (mask > 0) {
			Pair cur = dp[mask][i];
			words[i].getChars(0, words[i].length(), res[cur.r], cur.c-words[i].length());

			int j = pred[mask][i];
			mask = mask ^ (1 << i);
			i = j;
		}
		
		for (char[] row: res)
			System.out.println(new String(row));
	}
}
