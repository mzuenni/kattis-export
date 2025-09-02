import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class PantsOnFireChris_NoWorst {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		HashMap<String, HashSet<String>> worse = new HashMap<>();

		for (int i = 0; i < n; i++) {

			String s1 = sc.next();
			sc.next(); // are
			sc.next(); // worse
			sc.next(); // than
			String s2 = sc.next();

			worse.putIfAbsent(s1, new HashSet<String>());
			worse.get(s1).add(s2);

		}

		for (int i = 0; i < m; i++) {
			String s1 = sc.next();
			sc.next(); // are
			sc.next(); // worse
			sc.next(); // than
			String s2 = sc.next();

			boolean fact = reachable(s1, s2, worse);
			boolean altfact = reachable(s2, s1, worse);

			if (fact) {
				System.out.println("Fact");
			} else if (altfact) {
				System.out.println("Alternative Fact");
			} else {
				System.out.println("Pants on Fire");
			}
		}
	}

	private static boolean reachable(String s1, String s2, HashMap<String, HashSet<String>> worse) {
		HashSet<String> visited = new HashSet<>();
		Queue<String> q = new LinkedList<String>();
		q.add(s1);
		while (!q.isEmpty()) {
			String s = q.poll();
			if (s.equals(s2)) {
				return true;
			}
			visited.add(s);
			if (worse.containsKey(s)) {
				for (String t : worse.get(s)) {
					if (!visited.contains(t)) {
						q.add(t);
					}
				}
			}
		}
		return false;
	}
}
