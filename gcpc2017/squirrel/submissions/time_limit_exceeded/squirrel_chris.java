import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Scanner;

public class squirrel_chris {
	
	public static final int INF = 100000; // not MAX_VALUE to ignore overflows
	public static final boolean[] BOOLS = new boolean[] { true, false };
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int r = sc.nextInt()-1;
		int h = sc.nextInt()-1;
		int m = sc.nextInt()-1;

		ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
		for (int i = 0; i < n; i++) {
			graph.add(new ArrayList<>());
		}

		for (int i = 0; i < n - 1; i++) {
			int s = sc.nextInt()-1;
			int t = sc.nextInt()-1;
			graph.get(s).add(t);
			graph.get(t).add(s);
		}

		int[][][] memo = new int[n][n][n];

		int res = solve(r, h, m, memo, graph, n);
		System.out.println(res);
	}

	private static int solve(int r, int h, int m, int[][][] memo, ArrayList<ArrayList<Integer>> graph, int n) {
		// get already computed result
		if (memo[r][h][m] != 0) {
			return memo[r][h][m];
		}
		if (memo[r][m][h] != 0) {
			return memo[r][m][h];
		}
		// ignore computations on the stack
		memo[r][h][m] = INF;

		if (r == h || r == m) {
			memo[r][h][m] = 0;
			return 0;
		}

		// r is in a leaf with adjacent raven
		List<Integer> out = graph.get(r);
		if (out.size() == 1 && ((out.get(0) == r) || (out.get(0) == h))) {
			memo[r][h][m] = 1;
			return 1;
		}
		
		// All possible combinations of one raven flying and r moving
		// raven will minimize, squirrel maximise
		int min = Integer.MAX_VALUE;
		
		// if first is true, h moves, otherwise m
		for (boolean first : BOOLS) {
			// only move ravens to where the squirrel could move
			// if h moves, m blocks etc
			List<Integer> moveto = reach(graph, r, first ? m : h, n);
			for (int raven : moveto) {
				if (raven != h && raven != m) {
					int max = max(r, raven, h, m, first, memo, graph, n);
					if (max + 1 < min) {
						min = max + 1;
					}
				}
			}
		}
		
		memo[r][h][m] = min;
		return min;
	}
	
	private static int max(int r, int raven, int h, int m, boolean first, int[][][] memo, ArrayList<ArrayList<Integer>> graph, int n) {
		List<Integer> reach = reach(graph, r, first ? m : h, n); // first = true -> h moves, m blocks
		int max = 0;
		for (int rNew : reach) {
			int res = solve(rNew, first ? raven : h, first ? m : raven, memo, graph, n);
			if (res > max) {
				max = res;
			}
		}
		return max;
	}

	private static List<Integer> reach(ArrayList<ArrayList<Integer>> graph, int from, int block, int n) {
		
		ArrayList<Integer> res = new ArrayList<>();
		boolean[] visited = new boolean[n];
		
		Queue<Integer> tovisit = new LinkedList<Integer>();
		tovisit.add(from);
		
		while(!tovisit.isEmpty()) {
			int v = tovisit.poll();
			if (visited[v] || block == v) {
				continue;
			}
			res.add(v);
			visited[v] = true;
			for (int w : graph.get(v)) {
				if (!(visited[w] || block == w)) {
					tovisit.add(w);
				}
			}
		}
		return res;
	}
}
