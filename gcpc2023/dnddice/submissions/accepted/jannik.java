import java.util.*;
import java.math.*;

public class jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		final int[] vals = new int[]{4,6,8,12,20};
		final int n = vals.length;
		int[] cnt = new int[n];
		int r = 0, l = 0;
		for (int i = 0; i < n; i++) {
			cnt[i] = in.nextInt();
			r += cnt[i] * vals[i];
			l += cnt[i];
		}

		BigInteger[] count = new BigInteger[r+1];
		for (int i = 0; i <= r; i++)
			count[i] = (i == 0 ? BigInteger.ONE : BigInteger.ZERO);

		for (int i = 0; i < n; i++)
			while (cnt[i]-- > 0) {
				BigInteger[] n_c = new BigInteger[r+1];
				for (int j = 0; j <= r; j++) n_c[j] = BigInteger.ZERO;

				for (int x = 0; x + vals[i] <= r; x++)
					for (int v = 1; v <= vals[i]; v++)
						n_c[x + v] = n_c[x + v].add(count[x]);

				count = n_c;
			}

		final BigInteger[] java_is_stupid = count;
		Integer[] order = new Integer[r+1-l];
		for (int i = l; i <= r; i++) order[i - l] = i;
		Arrays.sort(order, (lhs, rhs) -> java_is_stupid[rhs].compareTo(java_is_stupid[lhs]));
		for (Integer i : order)
			System.out.print(i + " ");
	}
}
