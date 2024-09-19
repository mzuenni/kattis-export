import java.util.*;

public class jannik {
	static final long M = 1000000007;
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), k = in.nextInt();
		int[] a = new int[k+1];
		for (int i = 0; i < k; i++) a[i] = in.nextInt();

		long[] fac = new long[n+1];
		fac[0] = 1;
		for (int i = 1; i <= n; i++) fac[i] = (fac[i-1] * i) % M;

		int[] pfx = new int[k+1];
		pfx[0] = a[0];
		for (int i = 1; i < k; i++)
			pfx[i] = pfx[i-1] + a[i];
		pfx[k++] = n;

		long[] D = new long[k];

		for (int i = 0; i < k; i++) {
			for (int j = 0; j < i; j++)
				D[i] += (D[j] * (fac[pfx[i] - pfx[j]])) % M;
			D[i] = M + fac[ pfx[i] ] - (D[i] % M);
			D[i] %= M;
		}
		System.err.println(Arrays.toString(D));
		System.out.println(D[k-1]);
	}
}
