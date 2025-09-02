import java.util.*;

class solution {
	int m, n, k;
	List<Integer>[] adj;
	int[] pred;
	boolean[] mark;

	boolean find_match(int i) {
		if (i == -1) return true;
		for (int j: adj[i]) {
			if (mark[j]) continue;
			mark[j] = true;
			if (find_match(pred[j])) {
				pred[j] = i;
				return true;
			}
		}
		return false;
	}

	int max_matching(int from, int to) {
		int res = 0;
		for (int i = from; i < to; i++) {
			Arrays.fill(mark, false);
			if (find_match(i)) res++;
		}
		return res;
	}

	void run() {
		Scanner sc = new Scanner(System.in);
		m = sc.nextInt();
		n = sc.nextInt();
		k = sc.nextInt();

		adj = new ArrayList[m+2];
		for (int i = 0; i < m; i++) adj[i] = new ArrayList<>();
		pred = new int[n];
		Arrays.fill(pred,-1);
		mark = new boolean[n];
		
		for (int i = 0; i < k; i++) {
			int a = sc.nextInt() - 1;
			int b = sc.nextInt() - 1;
			adj[a].add(b);
		}
		
		int match_base = max_matching(0,m), match_extra = 0;
		int[] old_pred = pred.clone();

		for (int i = 0; i < m; i++) {
			System.arraycopy(old_pred,0,pred,0,n);
			adj[m] = adj[m+1] = adj[i];
			match_extra = Math.max(match_extra, max_matching(m,m+2));
		}
		System.out.println(match_base + match_extra);
	}
}

public class paul_Scanner {
	public static void main(String[] args) {
		solution s = new solution();
		s.run();
	}
}
