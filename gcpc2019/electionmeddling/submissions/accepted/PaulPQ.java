import java.util.*;

public class PaulPQ {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt(), m = sc.nextInt();

		int[] cost = new int[n];
		for (int i = 0; i < n; i++) {
			int x = sc.nextInt();

			PriorityQueue<Integer> Q = new PriorityQueue<>((a,b) -> Integer.compare(b,a));
			for (int j = 0; j < m-1; j++) Q.add(sc.nextInt());

			while (x <= Q.peek()) {
				x++;
				cost[i]++;
				Q.add(Q.poll()-1);
			}
		}
		Arrays.sort(cost);

		int res = 0;
		for (int i = 0; i < n/2+1; i++) res += cost[i];
		System.out.println(res);
	}
}
