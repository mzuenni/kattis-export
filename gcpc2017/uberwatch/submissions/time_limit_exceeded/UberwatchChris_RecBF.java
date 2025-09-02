import java.util.Scanner;

public class UberwatchChris_RecBF {
	public static long solve(int i, int m, long[] ops) {
		if (i < m) {
			return 0;
		}
		return Math.max(solve(i-1, m, ops), solve(i-m, m, ops) + ops[i]);
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		long[] ops = new long[n];

		for (int i = 0; i < n; i++) {
			ops[i] = sc.nextLong();
		}
		System.out.println(solve(n-1, m, ops));
		sc.close();
	}
}
