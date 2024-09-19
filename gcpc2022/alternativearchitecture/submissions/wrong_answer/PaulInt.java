import java.math.*;
import java.util.*;

public class PaulInt {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int a = sc.nextInt();
		int b = sc.nextInt();
		int g = BigInteger.valueOf(a).gcd(BigInteger.valueOf(b)).intValue();

		int res = 1;
		for (int x = 1; x < g; x++) {
			int y = (int) Math.round(Math.sqrt(g*g - x*x));
			if (x*x + y*y == g*g) res++;
		}
		if (a != b) res *= 2;
		System.out.println(res);
	}
}
