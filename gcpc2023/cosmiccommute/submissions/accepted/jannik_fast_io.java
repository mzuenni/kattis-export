import java.util.*;
import java.io.*;

public class jannik_fast_io {
	static class IntList extends ArrayList<Integer> {}
	static int[] bfs(IntList[] adj, int s) {
		int[] dist = new int[adj.length];
		for (int i = 0; i < adj.length; i++) dist[i] = Integer.MAX_VALUE;
		dist[s] = 0;
		ArrayDeque<Integer> q = new ArrayDeque<>();
		q.add(s);
		while (!q.isEmpty()) {
			int i = q.poll();
			for (int j : adj[i])
				if (dist[j] > dist[i] + 1) {
					dist[j] = dist[i] + 1;
					q.add(j);
				}
		}
		return dist;
	}
	static int nextInt(StringTokenizer st) {
		return Integer.parseInt(st.nextToken());
	}
	public static long gcd(long a, long b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		int n = nextInt(st), m = nextInt(st);
		long k = nextInt(st);
		
		int[] wormholes = new int[(int)k];
		st = new StringTokenizer(br.readLine());
		for (int i = 0; i < k; i++)
			wormholes[i] = nextInt(st) - 1;
		IntList[] adj = new IntList[n];
		for (int i = 0; i < n; i++)
			adj[i] = new IntList();
		while (m-- > 0) {
			st = new StringTokenizer(br.readLine());
			int u = nextInt(st) - 1, v = nextInt(st) - 1;
			adj[u].add(v);
			adj[v].add(u);
		}

		int[] dist_s = bfs(adj, 0);
		int[] dist_t = bfs(adj, n-1);
		long sum_t = 0;
		for (int i : wormholes) sum_t += dist_t[i];
		long res = (k-1)*dist_s[n-1];
		for (int i : wormholes)
			res = Math.min(res, (k-1)*dist_s[i] + sum_t - dist_t[i]);
		long g = gcd(res, k-1);
		System.out.printf("%d/%d\n", res/g,(k-1)/g);
	}
}
