import java.util.*;

public class Paul {
	public static void main(String[] args) {
		long n = new Scanner(System.in).nextLong();
		n = Math.min(n,100);
		double a = 100, b = 0, c = 0, d = 100;
		for (int i = 1; i < n; i++) {
			double e = (a+c)/2, f = (b+d)/2;
			a = c;
			b = d;
			c = e;
			d = f;
		}
		System.out.println(a + " " + b);
	}
}
