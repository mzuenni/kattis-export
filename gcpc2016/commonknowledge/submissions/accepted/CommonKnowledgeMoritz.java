import java.math.BigInteger;
import java.util.Scanner;

public class CommonKnowledgeMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		
		BigInteger res = BigInteger.valueOf(8);
		System.out.println(res.pow(n));
	}
}
