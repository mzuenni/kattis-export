import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Checktree {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int r = sc.nextInt();
		int h = sc.nextInt();
		int m = sc.nextInt();

		ArrayList<Integer>[] out = new ArrayList[n];

		for (int i = 0; i < n - 1; i++) {

			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;

			if (out[a] == null) {
				out[a] = new ArrayList<Integer>();
			}
			if (out[b] == null) {
				out[b] = new ArrayList<Integer>();
			}

			out[a].add(b);
			out[b].add(a);

		}

		Queue<Integer> q = new LinkedList<Integer>();
		q.add(0);

		boolean[] visited = new boolean[n];

		while (!q.isEmpty()) {

			int next = q.poll();
			if (!visited[next]) {
				visited[next] = true;

				for (Integer nex : out[next]) {
					if (!visited[nex]) {
						q.add(nex);
					}
				}
			}
		}
		boolean all = true;
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				all = false;
				break;
			}
		}
		
		if (!all) {
			System.err.println("Not connecting all nodes");
			System.exit(43);
		}
		System.exit(42);
	}
}
