import java.util.*;

public class jannik_precision {
	// type: 0 for triangle, 1 for circle, 2 for square
	static long grundy(long a, int type) {
		assert a > 0;
		if (type == 0) return a - 1;
		if (type == 1 && a == 1) return 2;
		if (type == 2) return (long) (a*4.0 / (Math.sqrt(6) + Math.sqrt(2)));
		return (long) (a * Math.sqrt(3)); // type == 1
	}
	static boolean fits(double a1, int t1, double a2, int t2) {
		if (t1 == t2) return a1 < a2;
		if (t1 == 0 && t2 == 1) // triangle in a circle
			return a1*a1 < 3 * a2*a2;
		if (t1 == 0 && t2 == 2) { // triangle in square
			double d = 2*a2*a2 - a1*a1;
			return d > 0 && a1*a1*a1*a1 * 3 < 4*d*d;
		}
		if (t1 == 1 && t2 == 0) // circle in a triangle
			return a1*a1*12 < a2*a2;
		if (t1 == 1 && t2 == 2) // circle in square
			return a1 * 2.0 < a2;
		if (t1 == 2 && t2 == 0) // square in triangle
			return 4*a1*a1 < 3*(a2 - a1)*(a2 - a1);
		assert t1 == 2 && t2 == 1; // square in circle
		return a1*a1 < 2*a2*a2;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();

		long[] nim = new long[n];
		long[] a = new long[n];
		int[] type = new int[n];
		
		for (int i = 0; i < n; i++) {
			String t = in.next();
			a[i] = in.nextLong();

			type[i] = t.charAt(0) == 't' ? 0 : t.charAt(0) == 'c' ? 1 : 2;
			nim[i] = grundy(a[i], type[i]);
		}

		long total = 0;
		for (int i = 0; i < n; i++) total ^= nim[i];

		int res = 0;
		for (int i = 0; i < n; i++) {
			final long tar = total ^ nim[i];
			// check for each type whether we can achieve
			// grundy number tar fitting into type[i]|a[i]
			for (int t = 0; t < 3; t++) {
				long lo = 1, hi = (long)3.1e9;
				while (lo + 1 < hi) {
					long m = (hi + lo) / 2;
					if (grundy(m, t) <= tar)
						lo = m;
					else
						hi = m;
				}
				if (fits(lo, t, a[i], type[i]) && grundy(lo, t) == tar)
					res++;
			}
		}
		System.out.println(res);
	}
}
