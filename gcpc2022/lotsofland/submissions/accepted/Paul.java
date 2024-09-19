import java.util.*;

public class Paul {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int h = sc.nextInt();
		int w = sc.nextInt();
		int n = sc.nextInt();
		
		for (int a = 1; a <= h; a++) {
			if (h%a != 0) continue;
			for (int b = 1; b <= w; b++) {
				if (w%b != 0) continue;
				if ((h/a)*(w/b) != n) continue;

				char[][] res = new char[h][w];
				for (int i = 0; i < h; i++) {
					for (int j = 0; j < w; j++) {
						res[i][j] = (char) ('a' + (i/a)*(w/b) + j/b);
					}
				}

				for (char[] row: res) {
					System.out.println(new String(row));
				}
				return;
			}
		}

		System.out.println("impossible");
	}
}
