import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

// Java 17: sealed abstract classes
sealed abstract class Java17Test {}
final class C extends Java17Test {}

public class jeroenJava17 {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	static int n, k, todo;
	static boolean[][] done;
	static boolean[][] mem;

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		n = Integer.valueOf(ps[0]);
		k = Integer.valueOf(ps[1]);
		done = new boolean[n][n];
		mem = new boolean[n][n];

		// Keep track of whether we found them all
		todo = 5 * k;
		for(int x = 0; x < n; x++) {
			for(int y = x % 5; y < n; y += 5) {
				if(shoot(x, y)) {
					// Yay, we hit it, let's just go 5 steps away in each dir
					for(int z = 1; z < 5; z++) {
						shoot(x+z, y);
						shoot(x-z, y);
						shoot(x, y+z);
						shoot(x, y-z);
					}
				}
			}
		}
		throw new Exception("Did not find all ships!");
	}

	public static boolean shoot(int x, int y) throws Exception {
		if(x < 0 || x >= n || y < 0 || y >= n) return false;
		if(done[x][y]) return mem[x][y];
		done[x][y] = true;
		System.out.println((x+1) + " " + (y+1));
		mem[x][y] = !in.readLine().equals("miss");
		if(mem[x][y] && --todo == 0)
			System.exit(0);
		return mem[x][y];
	}
}
