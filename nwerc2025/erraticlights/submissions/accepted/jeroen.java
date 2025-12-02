import java.io.BufferedReader;
import java.io.InputStreamReader;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		int[] cnt = new int[3];
		String ps = in.readLine().trim();
		for (char p : ps.toCharArray())
			cnt["rgb".indexOf(p)]++;
		System.out.println(f(cnt[0], cnt[1], cnt[2]));
	}

	static double[][][] mem = new double[101][101][101];
	static boolean[][][] seen = new boolean[101][101][101];

	static double f(int a, int b, int c) {
		// Which color is which does not matter, so we just count
		// the groups and make a <= b <= c
		if (a > b)
			return f(b, a, c);
		if (b > c)
			return f(a, c, b);

		// Base case
		if (b == 0)
			return 0;

		// Cache the results for O(n^3) runtime
		if (seen[a][b][c])
			return mem[a][b][c];
		seen[a][b][c] = true;

		if (a > 0) {
			// 3 colors left, so we touch 'a'.
			// We get each of the 3 colors with equal
			// probability, so we have
			// f(a,b,c) = 1 + 1/3 f(a,b,c) + 1/3 f(a-1,b+1,c) + 1/3 f(a-1,b,c+1)
			// 2/3 f(a,b,c) = 1 + 1/3 f(a-1,b+1,c) + 1/3 f(a-1,b,c+1)
			// f(a,b,c) = 3/2 + 1/2 f(a-1,b+1,c) + 1/2 f(a-1,b,c+1)
			mem[a][b][c] = 1.5 + f(a - 1, b + 1, c)/2 + f(a - 1, b, c + 1)/2;
		} else {
			// 2 colors left, so we touch 'b'
			// Almost same as the above, we get:
			// f(0,b,c) = 1 + 1/3 f(1,b-1,c) + 1/3 f(0,b,c) + 1/3 f(0,b-1,c+1)
			// However, the important insight here is that
			// if we end up with either an a or b, we will again touch that
			// same bulb, so we have that
			// f(1,b-1,c) = f(0,b,c)
			// This gives
			// f(0,b,c) = 1 + 2/3 f(0,b,c) + 1/3 f(0,b-1,c+1)
			// 1/3 f(0,b,c) = 1 + 1/3 f(0,b-1,c+1)
			// f(0,b,c) = 3 + f(0,b-1,c+1)
			mem[a][b][c] = 3 + f(0, b - 1, c + 1);
		}

		return mem[a][b][c];
	}
}
