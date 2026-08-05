
import java.math.BigInteger;
import java.util.Scanner;

//ignores c and d

public class MatrixCypherPhilippWA {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		BigInteger a = sc.nextBigInteger();
		BigInteger b = sc.nextBigInteger();
		BigInteger c = sc.nextBigInteger();
		BigInteger d = sc.nextBigInteger();


		StringBuilder out = new StringBuilder();
		while (a.compareTo(BigInteger.ONE) != 0 || b.compareTo(BigInteger.ZERO) != 0) {
			if (a.compareTo(b) <= 0) {
				b = b.subtract(a);
				out.append('1');
			} else {
				a = a.subtract(b);
				out.append('0');
			}
		}
		System.out.println(out.reverse());
	}
}
