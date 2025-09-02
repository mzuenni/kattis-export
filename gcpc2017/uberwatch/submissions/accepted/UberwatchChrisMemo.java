import java.util.Arrays;
import java.util.Scanner;

public class UberwatchChrisMemo {
	public static long solve(int i, int m, long[] ops, long[] memo) {
		if (memo[i] != -1) {
			return memo[i];
		}
		if (i < m) {
			memo[i] = 0;
			return 0;
		}
		long res = Math.max(solve(i-1, m, ops, memo), solve(i-m, m, ops, memo) + ops[i]);
		memo[i] = res;
		return res;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		long[] ops = new long[n];

		for (int i = 0; i < n; i++) {
			ops[i] = sc.nextLong();
		}
		long[] memo = new long[n];
		Arrays.fill(memo, -1);
		System.out.println(solve(n-1, m, ops, memo));
		sc.close();
	}
}
