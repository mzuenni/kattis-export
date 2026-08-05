import java.math.*;
import java.util.*;

public class tobi {
	public static boolean prime(String s) {
		BigInteger n = new BigInteger(s);
		return n.isProbablePrime(50);
	}
	public static void main(String args[]) throws Exception {
		Scanner sc = new Scanner(System.in);
		String n = sc.next();
		if (prime(n) && prime(new StringBuffer(n).reverse().toString())) {
			System.out.println("yes");
		} else {
			System.out.println("no");
		}
	}
}
