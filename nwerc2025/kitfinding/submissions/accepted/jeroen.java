import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int h = Integer.valueOf(ps[0]);
		int w = Integer.valueOf(ps[1]);
		int k = Integer.valueOf(ps[2]);
		int i = Integer.valueOf(ps[3]);
		int t = Integer.valueOf(ps[4]);

		// Start with the word KIT in the left top
		char[][] grid = new char[h][w];
		grid[0][0] = 'K';
		grid[0][1] = 'I';
		grid[0][2] = 'T';

		// Fill the rest of the letters in order TKI, then we
		// can never make another instance of KIT
		int r = w == 3 ? 1 : 0;
		int c = w == 3 ? 0 : 3;
		k--;
		i--;
		t--;
		while(t > 0) {
			grid[r][c] = 'T';
			t--;
			c++;
			if(c == w) {
				c = 0;
				r++;
			}
		}
		while(k > 0) {
			grid[r][c] = 'K';
			k--;
			c++;
			if(c == w) {
				c = 0;
				r++;
			}
		}
		while(i > 0) {
			grid[r][c] = 'I';
			i--;
			c++;
			if(c == w) {
				c = 0;
				r++;
			}
		}
		
		// Print the answer
		for(r = 0; r < h; r++)
			System.out.println(new String(grid[r]));
	}
}
