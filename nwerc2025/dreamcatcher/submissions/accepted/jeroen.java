import java.io.BufferedReader;
import java.io.InputStreamReader;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());

		// Find the biggest k such that k and n are coprime
		int k = n / 2;
		while (gcd(k, n) > 1)
			k--;
		System.out.println(k);
	}

	static int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
}
