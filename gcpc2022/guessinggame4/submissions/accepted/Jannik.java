import java.util.*;

public class Jannik {
	static class IntList extends ArrayList<Integer> {}

	final static int MAXM = 2 * 101101;
	final static int MAXV = 2 * MAXM;

	final static int MAXN = 2 * MAXV;

	static IntList[] adj = new IntList[MAXN];
	static IntList[] rev_adj = new IntList[MAXN];
	static int ccomp;
	static int[] comp = new int[MAXN]; // output: component of each node
	static IntList st = new IntList(); // temp: stack
	static void dfs(int n, int c, boolean backward) {
		if (comp[n] != -1) return;
		comp[n] = c;
		for(int j : (backward ? rev_adj[n] : adj[n])) dfs(j, c, backward);
		if (!backward) st.add(n);
	}
	static void kosaraju(int n) {
		Arrays.fill(comp, -1);
		st.clear();
		for (int i = 0; i < n; ++i) dfs(i, 0, false);
		Arrays.fill(comp, -1);
		ccomp = 0;
		for (int i = n - 1; i >= 0; i--)
			if (comp[st.get(i)] == -1)
				dfs(st.get(i), ccomp++, true);
	}

	static void addImpl(int u, int v) {
		adj[u].add(v);
		rev_adj[v].add(u);
	}

	static void addClause(int v1, int v2) {
		addImpl(v1^1, v2);
		addImpl(v2^1, v1);
	}

	static boolean solvable(int varcnt) {
		kosaraju(2*varcnt);
		for (int i = 0; i < varcnt; i++)
			if (comp[2*i] == comp[2*i+1])
				return false;
		return true;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		int n = in.nextInt();

		int[] prefix = new int[10];
		int[] ngames = new int[10];
		prefix[0] = 0;
		for(int i=0; i<7;i++){
			ngames[i] = in.nextInt();
			prefix[i+1] = prefix[i] + ngames[i];
		}
		int m = prefix[7];

		for (int i = 0; i < 4*m; i++) {
			adj[i] = new IntList();
			rev_adj[i] = new IntList();
		}

		for (int i = 0; i < m; i++) {
			addClause(i << 1, (m + i) << 1);
			addClause((i << 1)^1, ((m+i) << 1)^1); // not really necessary
		}

		for (int k = 0; k < n; k++) {
			int[] b = new int[7];
			for (int i = 0; i < 7; i++) {
				b[i] = in.nextInt();
				b[i] = b[i] > 0 ? (prefix[i] + b[i] - 1) << 1 : (m + prefix[i] - b[i] - 1) << 1;
				for (int j = 0; j < i; j++)
					addClause(b[i]^1, b[j]^1);
			}
		}

		int a = in.nextInt(), b = in.nextInt();
		a = a > 0 ? (prefix[5] + a - 1) << 1 : (m + prefix[5] - a - 1) << 1;
		b = b > 0 ? (prefix[6] + b - 1) << 1 : (m + prefix[6] - b - 1) << 1;

		addImpl(a^1, a);
		addImpl(b^1, b);

		System.out.println(solvable(2*m) ? "possible" : "impossible");
	}
}
