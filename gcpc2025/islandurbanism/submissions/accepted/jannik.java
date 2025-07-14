import java.util.*;
import java.util.function.Function;

public class jannik {
	static final long oo = 0x3f3f3f3f3f3f3f3fL;

	static class Pair {
		public int x;
		public long y;

		Pair(int a, long b) {
			x = a;
			y = b;
		}
	}

	static class AdjList extends ArrayList<Pair> {
	}

	static class IntSet extends TreeSet<Integer> {
	}

	// n * 3^k + m * log n * 2^k
	static long[][] solve(AdjList[] g, Integer[] terminals) {
		final int n = g.length;
		long[][] mem = new long[1 << terminals.length][n];
		for (long[] m : mem)
			Arrays.fill(m, oo);
		int[] is_terminal = new int[n];
		for (int i = 0; i < terminals.length; i++)
			is_terminal[terminals[i]] = 1 << i;
		for (int i = 0; i < n; i++)
			mem[0][i] = 0;
		for (int S = 1; S < (1 << terminals.length); S++) {
			PriorityQueue<Pair> pq = new PriorityQueue<>((a, b) -> Long.compare(a.y, b.y));
			for (int i = 0; i < n; i++) {
				if ((S & is_terminal[i]) != 0)
					mem[S][i] = Math.min(mem[S][i], mem[S ^ is_terminal[i]][i]);
				for (int S2 = (S - 1) & S; S2 != 0; S2 = (S2 - 1) & S)
					mem[S][i] = Math.min(mem[S][i], mem[S2][i] + mem[S ^ S2][i]);
				if (mem[S][i] < oo)
					pq.add(new Pair(i, mem[S][i]));
			}
			while (!pq.isEmpty()) {
				Pair t = pq.poll();
				int i = t.x;
				long v = t.y;
				if (mem[S][i] != v)
					continue;
				for (Pair e : g[i])
					if (mem[S][e.x] > v + e.y)
						pq.add(new Pair(e.x, mem[S][e.x] = v + e.y));
			}
		}
		return mem;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		in.next(); // n
		int m = in.nextInt(), v = in.nextInt(), k = in.nextInt();
		AdjList[][] gs = new AdjList[v][];
		int[] u = new int[v];
		int[] s = new int[v + 1];
		for (int i = 0; i < v; i++) {
			u[i] = in.nextInt();
			gs[i] = new AdjList[u[i]];
			for (int j = 0; j < u[i]; j++)
				gs[i][j] = new AdjList();
			s[i + 1] = s[i] + u[i];
		}
		long[] next = new long[v];
		Arrays.fill(next, oo);
		Function<Integer, Integer> get_v = i -> {
			int lo = 0, hi = v + 1;
			while (lo + 1 < hi) {
				int mid = lo + (hi - lo) / 2;
				if (i >= s[mid])
					lo = mid;
				else
					hi = mid;
			}
			assert(s[lo] <= i);
			assert(s[hi] > i);
			return lo;
		};
		while (m-- > 0) {
			int a = in.nextInt() - 1, b = in.nextInt() - 1;
			long c = in.nextLong();
			int u_v = get_v.apply(a);
			int v_v = get_v.apply(b);
			if (u_v == v_v) {
				gs[u_v][a - s[u_v]].add(new Pair(b - s[u_v], c));
				gs[u_v][b - s[u_v]].add(new Pair(a - s[u_v], c));
			} else if ((u_v + 1) % v == v_v)
				next[u_v] = Math.min(next[u_v], c);
			else
				next[v_v] = Math.min(next[v_v], c);
		}
		IntSet[] terminals = new IntSet[v];
		for (int i = 0; i < v; i++)
			terminals[i] = new IntSet();
		for (int mm = k, x; mm-- > 0;) {
			x = in.nextInt() - 1;
			terminals[get_v.apply(x)].add(x - s[get_v.apply(x)]);
		}

		long[] conn_l = new long[v], conn_r = new long[v], conn_both = new long[v], conn_lr = new long[v];
		long res = oo;
		for (int i = 0; i < v; i++) {
			IntSet tmp = (IntSet) terminals[i].clone();
			tmp.add(0);
			tmp.add(u[i] - 1);
			int k_v = tmp.size(), nn = gs[i].length;
			int first = ~(terminals[i].contains(0) ? 0 : 1);
			int last = ~(terminals[i].contains(nn - 1) ? 0 : (1 << (k_v - 1)));
			Integer[] tmpArr = new Integer[tmp.size()];
			tmp.toArray(tmpArr);
			long[][] dp = solve(gs[i], tmpArr);
			int everyone = (1 << k_v) - 1;
			conn_both[i] = dp[everyone][0];
			conn_r[i] = dp[everyone & first][nn - 1];
			conn_l[i] = dp[everyone & last][0];
			if (k == terminals[i].size())
				res = Math.min(res, dp[everyone & first & last][terminals[i].first()]);
			conn_lr[i] = conn_both[i];
			for (int mask = (1 << (k_v - 1)); mask < (1 << k_v); mask += 2)
				conn_lr[i] = Math.min(conn_lr[i], dp[mask][nn - 1] + dp[everyone ^ mask][0]);
		}

		for (int i = 0; i < v; i++) {
			// cut before i
			long tmp = conn_r[i];
			for (int x = k - terminals[i].size(), j = 1; j < v && x > 0; j++) {
				tmp += next[(i + j - 1) % v];
				int ii = (i + j) % v;
				tmp += (x == terminals[ii].size()) ? conn_l[ii] : conn_both[ii];
				x -= terminals[ii].size();
			}
			res = Math.min(res, tmp);

			// cut in i
			tmp = conn_lr[i];
			tmp += Arrays.stream(conn_both).sum() - conn_both[i];
			tmp += Arrays.stream(next).sum();
			res = Math.min(res, tmp);
		}
		System.out.println(res);
	}
}
