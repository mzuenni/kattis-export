import java.util.*;

public class Jannik {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), q = in.nextInt();
		TreeSet<Integer> closed = new TreeSet<>();
		while (q-- > 0) {
			char c = in.next().charAt(0);
			int a = in.nextInt();
			if (c == '-') {
				closed.add(a);
			} else if (c == '+') {
				closed.remove(a);
			} else {
				int b = in.nextInt();
				if (a > b) { int tmpA = a; a = b; b = tmpA; }
				boolean possible = !closed.contains(a) && !closed.contains(b);
				if (possible) {
					Integer pa = closed.lower(a);
					Integer pb = closed.higher(b);
					possible = false;
					if (pa == null && pb == null) possible = true;
					if (!possible) {
						pa = closed.higher(a);
						if (pa == null || pa > b)
							possible = true;
					}
				}
				System.out.print(possible ? "possible\n" : "impossible\n");
			}
		}
	}
}
