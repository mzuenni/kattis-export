
import java.math.BigInteger;
import java.util.Scanner;

public class MatrixCypherPhilipp {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		BigInteger a = sc.nextBigInteger();
		BigInteger b = sc.nextBigInteger();
		BigInteger c = sc.nextBigInteger();
		BigInteger d = sc.nextBigInteger();



		StringBuilder out = new StringBuilder();
		while (b.compareTo(BigInteger.ZERO) != 0 || c.compareTo(BigInteger.ZERO) != 0) {
			if (a.compareTo(b) > 0) {
				a = a.subtract(b);
				c = c.subtract(d);
				out.append('0');
			} else {
				b = b.subtract(a);
				d = d.subtract(c);
				out.append('1');
			}
		}
		System.out.println(out.reverse());
	}
}
