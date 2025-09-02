import java.util.Scanner;

public class UberwatchChris_StartOff {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		long[] ops = new long[n];

		for (int i = 0; i < n; i++) {
			ops[i] = sc.nextLong();
		}

		long[] dp = new long[n];

		for (int i = 1; i < n; i++) {
			dp[i] = dp[i-1];
			if (i > m) {
				dp[i] = Math.max(dp[i], dp[i - m] + ops[i]);
			}
		}
		System.out.println(dp[n - 1]);
	}
}
