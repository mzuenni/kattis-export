
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class SellingPhilipp {
	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		int c = sc.nextInt();
		int m = sc.nextInt();
		int[][] prices = new int[m][c+1];
		for (int i = 0; i < prices.length; i++) {
			for (int j = 1; j < prices[i].length; j++) {
				prices[i][j] = sc.nextInt();
			}
		}
		int[][] dp = new int[m][c+1];
		dp[0] = prices[0];
		for (int merch = 1; merch < dp.length; merch++) {
			for (int amount = 0; amount < prices[merch].length; amount++) {
				for (int sold = 0; sold+amount<dp[merch].length; sold++) {
					dp[merch][sold+amount]=Math.max(dp[merch][sold+amount], dp[merch-1][sold]+prices[merch][amount]);
				}
			}
		}
		int max = 0;
		for (int amount = 0; amount <= c; amount++) {
			max=Math.max(max,dp[m-1][amount]);
		}
		System.out.println(max);
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
