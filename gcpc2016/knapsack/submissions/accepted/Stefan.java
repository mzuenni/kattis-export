import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * This is a solution for the knapsack problem. We use the classical approach
 * for the knapsack problem but compute everything modulo the lightest item.
 * Also, we do not go through the array ordered by the keys but the values which
 * omits many updates.
 * 
 * @author Stefan Toman (toman@tum.de)
 */
public class Stefan {

	public static void main(String[] args) throws IOException {
		// read the input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] nk = in.readLine().split(" ");
		int n = Integer.parseInt(nk[0]);
		long k = Long.parseLong(nk[1]);
		String[] tmp = in.readLine().split(" ");
		int[] g = new int[n];
		for (int i = 0; i < n; i++) {
			g[i] = Integer.parseInt(tmp[i]);
		}

		// sort weights
		Arrays.sort(g);

		// what can be done modulo g[0]?
		long[] min = new long[g[0]];
		Arrays.fill(min, Long.MAX_VALUE);
		min[0] = 0;
		PriorityQueue<Item> q = new PriorityQueue<>();
		q.add(new Item(0, 0));
		while (!q.isEmpty()) {
			int j = q.poll().key;
			for (int i = 1; i < n; i++) {
				if (min[j] <= k && min[(j + g[i]) % g[0]] > min[j] + g[i]) {
					int t = (j + g[i]) % g[0];
					min[t] = min[j] + g[i];
					q.add(new Item(t, min[t]));
				}
			}
		}

		// output
		System.out.println(min[(int) (k % g[0])] <= k ? "possible" : "impossible");
	}

	static class Item implements Comparable<Item> {
		int key;
		long value;

		public Item(int key, long value) {
			this.key = key;
			this.value = value;
		}

		@Override
		public int compareTo(Item arg) {
			return (int) Math.signum(value - arg.value);
		}
	}
}
