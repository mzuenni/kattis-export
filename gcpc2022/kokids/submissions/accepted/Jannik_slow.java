import java.util.*;

public class Jannik_slow {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt(), k = in.nextInt();
		String s = in.next();
		int num = 0; // number of known steps
		int fallen = 0;
		for (int i = 0; i < k; i++) { // just simulate each player
			char last = 'R';
			for (int p = 0; p < n; p++) {
				if (p < num) {
					// ok
					last = s.charAt(p);
				} else {
					num++;
					if (s.charAt(p) != last) { // ok
						last = s.charAt(p);
					} else { // fall
						fallen++;
						break;
					}
				}
			}
		}
		System.out.println(k-fallen);
	}
}
