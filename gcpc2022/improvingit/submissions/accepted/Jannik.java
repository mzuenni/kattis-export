import java.util.*;

public class Jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), m = in.nextInt();
		long[] cost = new long[n+1];
		Arrays.fill(cost, Long.MAX_VALUE);
		cost[0] = 0;
		for (int i = 0; i < n; i++) {
			final long c0 = in.nextLong();
			final int v = Math.min(m, n - i);
			for (int j = 1; j <= v; j++) {
				long cj = in.nextLong();
				cost[i+j] = Math.min(cost[i+j], cost[i] + c0 - cj);
			}
		}
		System.out.println(cost[n]);
	}
}
