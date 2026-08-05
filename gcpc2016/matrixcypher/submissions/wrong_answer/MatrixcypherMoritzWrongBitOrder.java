import java.math.BigInteger;
import java.util.Scanner;

public class MatrixcypherMoritzWrongBitOrder {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		BigInteger a = new BigInteger(sc.next());
		BigInteger b = new BigInteger(sc.next());
		BigInteger c = new BigInteger(sc.next());
		BigInteger d = new BigInteger(sc.next());
		
		String result="";
		while(a.compareTo(BigInteger.ONE) != 0 || b.compareTo(BigInteger.ZERO) != 0 || c.compareTo(BigInteger.ZERO) != 0 || d.compareTo(BigInteger.ONE) != 0) {
			
			if(a.compareTo(b) > 0 || c.compareTo(d) > 0) {
				a = a.subtract(b);
				c = c.subtract(d);
				result+='0';
			} else {
				b = b.subtract(a);
				d = d.subtract(c);
				result+='1';
			}
		}
		System.out.println(result);
	}
	
}
