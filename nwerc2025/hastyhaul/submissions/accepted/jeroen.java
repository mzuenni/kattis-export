import java.io.BufferedReader;
import java.io.InputStreamReader;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	static long[][] choose = new long[65][65];

	public static void main(String[] args) throws Exception {
		// Precompute
		choose[0][0] = 1;
		for(int i = 0; i < 65; i++) {
			for(int j = 0; j < 65; j++) {
				if (i > 0) {
					choose[i][j] += choose[i - 1][j];
					if (j > 0)
						choose[i][j] += choose[i - 1][j - 1];
				}
			}
		}

		// Read input
		int t = Integer.valueOf(in.readLine());
		while (t-- > 0) {
			String[] ps = in.readLine().split(" ");
			int h = Integer.valueOf(ps[0]);
			int w = Integer.valueOf(ps[1]);
			String[] lines = new String[h];
			for (int i = 0; i < h; i++)
				lines[i] = in.readLine();

			// Make a bitmask of the state, and count number of 1's
			long mask = 0;
			int m = 0;
			int n = w * h;
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					if (lines[i].charAt(j) != '.') {
						mask |= 1L << (i * w + j);
						m++;
					}
				}
			}

			// If there is an odd number of states, there is no valid solution
			if (choose[n][m] % 2 > 0) {
				System.out.println("risky");
				continue;
			}

			// If we enumerate all states of length n with m ones,
			// such that adjacent states differ in exactly 2 positions,
			// we can index the states and return the one right next to
			// it (to left for odd positions, to the right for even positions).
			long idx = index(n, m, mask);
			long next = state(n, m, idx ^ 1);

			// Find the from move
			for (int i = 0; i < n; i++) {
				if (((1L << i) & mask) != 0 && ((1L << i) & next) == 0) {
					int r = i / w;
					int c = i % w;
					System.out.println((r + 1) + " " + (c + 1));
				}
			}

			// And then the to move
			for (int i = 0; i < n; i++) {
				if (((1L << i) & mask) == 0 && ((1L << i) & next) != 0) {
					int r = i / w;
					int c = i % w;
					System.out.println((r + 1) + " " + (c + 1));
				}
			}
		}
	}

	// Index number of the given state
	static long index(int n, int m, long mask) {
		if (n == 0)
			return 0;

		if ((mask & 1) == 0) {
			return index(n - 1, m, mask >> 1);
		} else {
			return choose[n - 1][m - 1] - (index(n - 1, m - 1, mask >> 1) - choose[n - 1][m]) - 1;
		}
	}

	// Inverse of index, we have that
	// state(n, m, index(n, m, i)) == i
	static long state(int n, int m, long index) {
		if (n == 0)
			return 0;

		long c = choose[n - 1][m];
		if (index < c) {
			return state(n - 1, m, index) << 1;
		} else {
			return (state(n - 1, m - 1, choose[n - 1][m - 1] - index + c - 1) << 1) | 1;
		}
	}

	static String toBinary(int n, long mask) {
		String ret= "";
		for(int i = 0; i < n; i++) {
			if((mask & 1) > 0) ret += "1";
			else ret += "0";
			mask >>= 1;
		}
		return ret;
	}
}
