// Adapted from Jannik.java

import java.util.*;
import java.io.*;

public class julian {
	public static void main(String[] args) throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String[] tmp = reader.readLine().split(" ");
		int n = Integer.parseInt(tmp[0]), q = Integer.parseInt(tmp[1]);
		TreeSet<Integer> closed = new TreeSet<>();
		while (q-- > 0) {
			tmp = reader.readLine().split(" ");
			char c = tmp[0].charAt(0);
			int a = Integer.parseInt(tmp[1]);
			if (c == '-') {
				closed.add(a);
			} else if (c == '+') {
				closed.remove(a);
			} else {
				int b = Integer.parseInt(tmp[2]);
				if (a > b) { int tmpA = a; a = b; b = tmpA; }
				boolean possible = true;
				Integer pa = closed.lower(a + 1);
				Integer pb = closed.higher(b - 1);
				possible = pa == null && pb == null;
				if (!possible) {
					pa = closed.higher(a - 1);
					if (pa == null || pa > b)
						possible = true;
				}
				System.out.print(possible ? "possible\n" : "impossible\n");
			}
		}
	}
}
