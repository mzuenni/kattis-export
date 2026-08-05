// copied from Philipp
// added extra check to reproduce orig vals
import java.math.BigInteger;
import java.util.Scanner;

public class MatrixTobi {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		BigInteger a = sc.nextBigInteger();
		BigInteger b = sc.nextBigInteger();
		BigInteger c = sc.nextBigInteger();
		BigInteger d = sc.nextBigInteger();
		BigInteger origa = new BigInteger(a.toString());
		BigInteger origb = new BigInteger(b.toString());
		BigInteger origc = new BigInteger(c.toString());
		BigInteger origd = new BigInteger(d.toString());

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
		out = out.reverse();
		System.out.println(out);

		BigInteger newa = BigInteger.ONE;
		BigInteger newb = BigInteger.ZERO;
		BigInteger newc = BigInteger.ZERO;
		BigInteger newd = BigInteger.ONE;
		for (char ch : out.toString().toCharArray()) {
			if (ch == '0') {
				newa = newa.add(newb);
				newc = newc.add(newd);
			} else {
				newb = newb.add(newa);
				newd = newd.add(newc);
			}
		}
		if (!newa.equals(origa) || !newb.equals(origb) || !newc.equals(origc) || !newd.equals(origd)) {
			System.err.println("mismatch!");
			System.exit(-1);
		}
	}
}
