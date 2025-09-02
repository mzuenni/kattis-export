import java.util.Random;
import java.util.Scanner;

public class ContestChaosGenerator {
	public static int roll(Random r, int min, int max) {
		return min + r.nextInt(max - min + 1);
	}

	public static String rollName(Random r) {
		int length = roll(r, 1, 30);
		StringBuilder b = new StringBuilder();
		for (int i = 0; i < length; i++) {
			b.append(alph[roll(r, 0, alph.length - 1)]);
		}
		return b.toString();
	}

	public static final char[] alph = { 'A', 'B', 'C', 'D', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		Random rand = new Random(sc.nextLong());
		final int N_MIN = sc.nextInt();
		final int N_MAX = sc.nextInt();

		final int START_MIN = sc.nextInt();
		final int START_MAX = sc.nextInt();
		
		final int LENGTH_MIN = sc.nextInt();
		final int LENGTH_MAX = sc.nextInt();
		
		final int P_MIN = sc.nextInt();
		final int P_MAX = sc.nextInt();
		
		sc.close();
		
		StringBuilder res = new StringBuilder();
		
		int n = roll(rand, N_MIN, N_MAX);
		res.append(n).append('\n');
		
		for (int i = 0; i < n; i++) {
			
			int start = roll(rand, START_MIN, START_MAX);
			int len = roll(rand, LENGTH_MIN, LENGTH_MAX);
			int p = roll(rand, P_MIN, P_MAX);

			String s = rollName(rand);
			
			res.append(start).append(" ").append(start+len).append(" ").append(p).append(" ").append(s).append("\n");
		}
		
		System.out.print(res);
	}
}
