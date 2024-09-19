import java.util.*;

public class jannik {
	public static void main(String[] args) {
		long n = new Scanner(System.in).nextLong();
		int res = (n < 10 ? 1 : 0);
		for (int d = 0; d < 10; d++) {
			long x = (d == 0 ? 10 : d);
			while (x <= n) {
				res++;
				x = 10 * x + d;
			}
		}
		System.out.println(res);
	}
}
