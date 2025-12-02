import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	static int n;
	static int[] a;
	static ArrayList<String> moves = new ArrayList<String>();
	static ArrayList<String> lastmoves = new ArrayList<String>();

	public static void main(String[] args) throws Exception {
		// Read input
		n = Integer.valueOf(in.readLine());
		a = new int[n];
		String[] ps = in.readLine().split(" ");
		for (int i = 0; i < n; i++)
			a[i] = Integer.valueOf(ps[i]);

		// The case of n higher than 5 is easy, we can just iteratively
		// move the highest number to the back and continue with a smaller
		// version
		while (n > 5) {
			// Find the highest number
			int i = 0;
			while (a[i] != n)
				i++;

			// Move it to the back, if it is position 0 or 1
			// we need two moves
			if (i == 0 || i == 1) {
				move(i, n - 3);
				move(n - 5, n - 3);
			} else if (i != n - 1) {
				move(i - 2, n - 3);
			}
			n--;
		}

		// For the last 5 numbers we need to be a bit smarter,
		// but the state-space is small enough so we just dfs
		// and hope for the best
		if(!dfs(a[0]-1,a[1]-1,a[2]-1,a[3]-1,a[4]-1))
			throw new Exception("No solution found");
		moves.addAll(lastmoves.reversed());

		// And print solution
		System.out.println(moves.size());
		for(String m : moves)
			System.out.println(m);
	}

	// i and j are 0-indexed here
	static void move(int i, int j) {
		int x = a[i];
		int y = a[i + 1];
		int z = a[i + 2];
		for (int k = i; k + 3 < n; k++) {
			a[k] = a[k + 3];
		}
		for (int k = n - 1; k > j + 2; k--) {
			a[k] = a[k - 3];
		}
		a[j] = x;
		a[j + 1] = y;
		a[j + 2] = z;

		moves.add((i + 1) + " " + (j + 1));
	}

	static boolean[][][][][] seen = new boolean[5][5][5][5][5];

	static boolean dfs(int a, int b, int c, int d, int e) {
		if (a < b && b < c && c < d && d < e)
			return true;
		if (seen[a][b][c][d][e])
			return false;
		seen[a][b][c][d][e] = true;

		// Manually spell out the 6 possible moves
		if (dfs(d, a, b, c, e)) {
			lastmoves.add("1 2");
			return true;
		}
		
		if (dfs(d, e, a, b, c)) {
			lastmoves.add("1 3");
			return true;
		}
		
		if (dfs(a, e, b, c, d)) {
			lastmoves.add("2 3");
			return true;
		}
		
		if (dfs(b, c, d, a, e)) {
			lastmoves.add("2 1");
			return true;
		}
		
		if (dfs(a, c, d, e, b)) {
			lastmoves.add("3 2");
			return true;
		}
		
		if (dfs(c, d, e, a, b)) {
			lastmoves.add("3 1");
			return true;
		}
		
		return false;
	}
}
