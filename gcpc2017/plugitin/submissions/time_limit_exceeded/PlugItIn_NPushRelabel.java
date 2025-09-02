import java.util.Scanner;

public class PlugItIn_NPushRelabel {
	static int INFINITY = Integer.MAX_VALUE;

	static void push(long[][] C, long[][] F, long[] excess, int u, int v) {
		double send = Math.min(excess[u], C[u][v] - F[u][v]);
		F[u][v] += send;
		F[v][u] -= send;
		excess[u] -= send;
		excess[v] += send;
	}

	static void relabel(long[][] C, long[][] F, int[] height, int[] count, int u) {
		int v;
		int min_height = INFINITY;
		count[height[u]]--;
		for (v = 0; v < C.length; v++) {
			if (C[u][v] - F[u][v] > 0) {
				min_height = Math.min(min_height, height[v]);
				height[u] = min_height + 1;
			}
		}
		count[height[u]]++;
	};

	static void discharge(long[][] C, long[][] F, long[] excess, int[] height, int[] count, int[] seen, int u) {
		while (excess[u] > 0) {
			if (seen[u] < C.length) {
				int v = seen[u];
				if ((C[u][v] - F[u][v] > 0) && (height[u] > height[v])) {
					push(C, F, excess, u, v);
				} else
					seen[u] += 1;
			} else {
				if (height[u] < C.length && count[height[u]] == 1) {
					gap(height[u], height, count);
				} else {
					relabel(C, F, height, count, u);
				}
				seen[u] = 0;
			}
		}
	}

	static void gap(int h, int[] height, int[] count) {
		int nodes = height.length;
		for (int i = 0; i < nodes; i++) {
			if (height[i] < h || height[i] >= nodes)
				continue;
			count[height[i]]--;
			height[i] = Math.max(height[i], nodes + 1);
			count[height[i]]++;
		}
	}

	static void moveToFront(int i, int[] A) {
		int temp = A[i];
		int n;
		for (n = i; n > 0; n--) {
			A[n] = A[n - 1];
		}
		A[0] = temp;
	}

	static long pushRelabel(long[][] C, long[][] F, int source, int sink) {
		long[] excess = new long[C.length];
		int[] height = new int[C.length], list = new int[C.length - 2], seen = new int[C.length];
		int[] count = new int[2 * C.length];
		int i, p;

		for (i = 0, p = 0; i < C.length; i++) {
			if ((i != source) && (i != sink)) {
				list[p] = i;
				p++;
			}
		}

		height[source] = C.length;
		count[C.length] = 1;
		count[0] = C.length - 1;
		excess[source] = INFINITY;
		for (i = 0; i < C.length; i++)
			push(C, F, excess, source, i);

		p = 0;
		while (p < C.length - 2) {
			int u = list[p];
			int old_height = height[u];
			discharge(C, F, excess, height, count, seen, u);
			if (height[u] > old_height) {
				moveToFront(p, list);
				p = 0;
			} else
				p += 1;
		}
		long maxflow = 0;
		for (i = 0; i < C.length; i++)
			maxflow += F[source][i];

		return maxflow;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int m = sc.nextInt(); // sockets
		int n = sc.nextInt(); // devices
		int k = sc.nextInt(); // connections
		
		int graphsize = m + n + 2;

		long[][] cap = new long[graphsize][graphsize];
		int source = 0;
		int target = 1;

		for (int i = 0; i < k; i++) {
			int a = sc.nextInt() + 1;
			int b = sc.nextInt() + m + 1;
			cap[a][b] += 1;
		}
		sc.close();
		
		for (int i = 2; i < m + 2; i++) {
			cap[source][i] = 1;
		}
		for (int i = m + 2; i < graphsize; i++) {
			cap[i][target] = 1;
		}

		long max = 0;
		for (int i = 2; i < m + 2; i++) {
			cap[source][i] = 3;
			long result = pushRelabel(cap, new long[graphsize][graphsize], source, target);
			cap[source][i] = 1;
			if (result > max) {
				max = result;
			}
		}

		System.out.println(max);
	}

}
