import java.util.*;

public class Leonard {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		int m = sc.nextInt();

		ArrayList<Integer>[] graph = new ArrayList[n];
		for (int i = 0; i < n; ++i) {
			graph[i] = new ArrayList<>();
		}

		for (int i = 0; i < m; ++i) {
			int u = sc.nextInt() - 1;
			int v = sc.nextInt() - 1;
			graph[u].add(v);
			graph[v].add(u);
		}

		int[][] dist = new int[n][2];

		for (int v = 0; v < n; ++v) {
			dist[v][0] = -1;
			dist[v][1] = -1;
		}

		Queue<Integer> q = new LinkedList<>();

		dist[n - 1][0] = 0;
		q.add(2 * (n - 1));

		while (!q.isEmpty()) {
			int v = q.peek() / 2;
			int x = q.poll() % 2;
			for (int u : graph[v]) {
				if (dist[u][0] == -1) {
					dist[u][0] = dist[v][x] + 1;
					q.add(2 * u);
				}
				else if (dist[u][1] == -1 && dist[v][x] == dist[u][0]) {
					dist[u][1] = dist[v][x] + 1;
					q.add(2 * u + 1);
				}
			}
		}

		System.out.println((dist[0][1] == -1 ? "im" : "") + "possible");
	}
}
