import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen_backtrack2 {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	static int h, w;
	static char[][] grid;

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		h = Integer.valueOf(ps[0]);
		w = Integer.valueOf(ps[1]);
		int k = Integer.valueOf(ps[2]);
		int i = Integer.valueOf(ps[3]);
		int t = Integer.valueOf(ps[4]);

		// Start with the word KIT in the left top
		grid = new char[h][w];
		grid[0][0] = 'K';
		grid[0][1] = 'I';
		grid[0][2] = 'T';

		// Fill the rest of the letters in a brute-force way
		if(!backtrack(w == 3 ? 1 : 0, w == 3 ? 0 : 3, k - 1, i - 1, t - 1))
			throw new Exception("No solution found");

		// Print the answer
		for(int r = 0; r < h; r++)
			System.out.println(new String(grid[r]));
	}

	public static boolean backtrack(int r, int c, int k, int i, int t) {
		if(k == 0 && i == 0 && t == 0) return true;

		if(t > 0) {
			grid[r][c] = 'T';
			if(check(r,c) && backtrack(c == w - 1 ? r + 1 : r, c == w - 1 ? 0 : c + 1, k, i, t - 1))
				return true;
		}

		if(i > 0) {
			grid[r][c] = 'I';
			if(check(r,c) && backtrack(c == w - 1 ? r + 1 : r, c == w - 1 ? 0 : c + 1, k, i - 1, t))
				return true;
		}
		
		if(k > 0) {
			grid[r][c] = 'K';
			if(check(r,c) && backtrack(c == w - 1 ? r + 1 : r, c == w - 1 ? 0 : c + 1, k - 1, i, t))
				return true;
		}

		return false;
	}

	// Check if we did not accidentally made the word KIT with the last
	// placed letter. Note: this code could be much nicer, but if you
	// don't know how to generalize then this might be more readable.
	public static boolean check(int r, int c) {
		// To the left
		if(c >= 2 && grid[r][c-2] == 'K' && grid[r][c-1] == 'I' && grid[r][c] == 'T')
			return false;
		if(c >= 2 && grid[r][c-2] == 'T' && grid[r][c-1] == 'I' && grid[r][c] == 'K')
			return false;

		// To the left top
		if(c >= 2 && r >= 2 && grid[r-2][c-2] == 'K' && grid[r-1][c-1] == 'I' && grid[r][c] == 'T')
			return false;
		if(c >= 2 && r >= 2 && grid[r-2][c-2] == 'T' && grid[r-1][c-1] == 'I' && grid[r][c] == 'K')
			return false;

		// To above
		if(r >= 2 && grid[r-2][c] == 'K' && grid[r-1][c] == 'I' && grid[r][c] == 'T')
			return false;
		if(r >= 2 && grid[r-2][c] == 'T' && grid[r-1][c] == 'I' && grid[r][c] == 'K')
			return false;

		// To right top
		if(r >= 2 && c < w - 2 && grid[r-2][c+2] == 'K' && grid[r-1][c+1] == 'I' && grid[r][c] == 'T')
			return false;
		if(r >= 2 && c < w - 2 && grid[r-2][c+2] == 'T' && grid[r-1][c+1] == 'I' && grid[r][c] == 'K')
			return false;

		// No KIT found
		return true;
	}
}
