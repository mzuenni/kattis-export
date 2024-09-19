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
					var hS = closed.headSet(a);
					var tS = closed.tailSet(b);
					possible = (hS.isEmpty() && tS.isEmpty()) || (hS.size() + tS.size() == closed.size());
				}
				System.out.print(possible ? "possible\n" : "impossible\n");
			}
		}
	}
}
