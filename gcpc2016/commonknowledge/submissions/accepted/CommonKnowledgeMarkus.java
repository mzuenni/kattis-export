import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class CommonKnowledgeMarkus {
	
	/**
	 * Fast exponentiation by successive squaring. Use of BigInteger.
	 * @param args
	 */
	public static void main(String[] args) {
		final Scanner s = new Scanner(System.in);
		final int n = s.nextInt();

		// Fast exponentiation (my try). 
		// In the contest, this should suffice in terms of runtime, i.e. one should not be punished if one does not use the (better) BigInteger.pow()
//		final String binary = Integer.toBinaryString(n);
//		long start = System.currentTimeMillis();
//		BigInteger pow = BigInteger.valueOf(8);
//		BigInteger eighToTheN = BigInteger.ONE;
//		for (int i = 1; i <= binary.length(); i++) {
//			if (binary.charAt(binary.length()-i) == '1')
//				eighToTheN = eighToTheN.multiply(pow);
//			if (i != binary.length())
//				pow = pow.multiply(pow);
//		}
//		long end = System.currentTimeMillis();
		
//		long start = System.currentTimeMillis();
		BigInteger eighToTheN = BigInteger.valueOf(8).pow(n);
//		long end = System.currentTimeMillis();
		try {
			BufferedWriter bf = new BufferedWriter(new OutputStreamWriter(System.out));
			bf.write(eighToTheN.toString());
			bf.write("\n");
//			bf.write((end-start)+" ms");
			bf.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
//		System.out.println(eighToTheN);	// Note that n = 0 works.
//		System.out.println((end-start)+" ms.");
		
		s.close();
	}
}
