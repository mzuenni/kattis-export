import java.math.*;
import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		long a = sc.nextInt() - 1;
		long b = sc.nextInt() - 1;
		long g = BigInteger.valueOf(a).gcd(BigInteger.valueOf(b)).longValue();

		int res = 1;
		for (long x = 1; x < g; x++) {
			long y = Math.round(Math.sqrt(g*g - x*x));
			if (x*x + y*y == g*g) res++;
		}
		if (a != b) res *= 2;
		System.out.println(res);
	}
}
