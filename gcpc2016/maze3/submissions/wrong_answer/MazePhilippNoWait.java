
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class MazePhilippNoWait {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int m = sc.nextInt();
		char[] letters = new char[m];
		
		ArrayList<HashMap<Character, Set<Integer>>> edges = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			edges.add(new HashMap<>());
		}
		for (int i = 0; i < m; i++) {
			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;
			char L = sc.next().charAt(0);
			if (!edges.get(a).containsKey(L)) {
				edges.get(a).put(L, new HashSet<>());
			}
			edges.get(a).get(L).add(b);
			if (!edges.get(b).containsKey(L)) {
				edges.get(b).put(L, new HashSet<>());
			}
			edges.get(b).get(L).add(a);
		}
		double[] prob = new double[n];
		double[] nextProb = new double[n];
		prob[0] = 1;
		String sequence = sc.next();
		sc.close();
		for (char c : sequence.toCharArray()) {
			for (int i = 0; i < n; i++) {
				if (edges.get(i).get(c) == null) {
					//nextProb[i] += prob[i];
					continue;
				}
				int size = edges.get(i).get(c).size();
				for (int j : edges.get(i).get(c)) {
					nextProb[j] += prob[i] * 1/size;
				}
			}
			double[] tmp = prob;
			prob = nextProb;
			nextProb = tmp;
			Arrays.fill(nextProb, 0);
		}
		System.out.println(prob[n - 1] * 100);
	}
}
