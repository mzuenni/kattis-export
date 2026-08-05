import java.util.*;
import java.math.*;

public class tobi_rho {
	public static Random rand = new Random();
	public static long N, ret = 1, factor;
	public static void factorize(long cur) {
		BigInteger bigN = new BigInteger("" + cur);
		if (bigN.isProbablePrime(50)) {
			long facCnt = 0;
			while (N % cur == 0) {
				facCnt++;
				N /= cur;
			}
			ret *= (1 + facCnt);
			if (N != 1) factorize(N);
		} else {
			while ((factor = rho(cur)) == 0) {}
			factorize(factor);
		}
	}
	public static long gcd(long a, long b) { return (b == 0) ? a : gcd(b, a%b); }
	public static long rho(long n) {
		long x, y, i = 1, k = 2, d;
		x = y = rand.nextLong() % n;
		while (true) {
			++i;
			x = (x*x + 2) % n;
			if(x == y) return 0;
			d = gcd(Math.abs(x-y),n);
			if(d != 1) return d;
			if(i == k) {
				y=x;
				k*=2;
			}
		}
	}
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextLong();
		factorize(N);
		System.out.println(ret);
	}
}
