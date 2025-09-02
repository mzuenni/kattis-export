/**
 * @author Christian Müller for GCPC 2017
 */

import java.math.BigInteger;
import java.util.Scanner;

public class BuildingsBigInteger {

	static final BigInteger MOD = BigInteger.valueOf(1000000007); // MOD ^ 2 fits into long
	
	public static long gcd(long a, long b) {
		return (b == 0) ? Math.abs(a) : gcd(b, a % b);
	}

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		long m = sc.nextLong();
		BigInteger c = sc.nextBigInteger();

		// number of c-colorings of an n by n square
		BigInteger col = c.pow(n * n);
		
		// number of possible necklaces different up to rotation with m beads in
		BigInteger sum = BigInteger.ZERO;
		for (long i = 0; i < m; i++) {

			int gcd = (int) gcd(m, i); // gcd < m
			BigInteger part = col.pow(gcd);
			sum = sum.add(part);
		}
		sum = sum.divide(BigInteger.valueOf(m)); // result is integral (Burnsides lemma)

		System.out.println(sum.mod(MOD));
	}
}
