import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Stack;
import java.util.TreeMap;
import java.util.Map.Entry;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	static int n;
	static int[] x1, y1, x2, y2;
	static PairII[] by_length;

	public static void main(String[] args) throws Exception {
		int t = Integer.valueOf(in.readLine());
		while (t-- > 0) {
			n = Integer.valueOf(in.readLine());
			x1 = new int[n];
			y1 = new int[n];
			x2 = new int[n];
			y2 = new int[n];
			for (int i = 0; i < n; i++) {
				String[] ps = in.readLine().split(" ");
				x1[i] = Integer.valueOf(ps[0]);
				y1[i] = Integer.valueOf(ps[1]);
				x2[i] = Integer.valueOf(ps[2]);
				y2[i] = Integer.valueOf(ps[3]);
			}

			System.out.println(solve() ? "yes" : "no");
		}
	}

	// This is shamelessly copied from paul.cpp
	static boolean solve() {
		by_length = new PairII[n];
		ArrayList<Event> events = new ArrayList<Event>();
		for (int i = 0; i < n; i++) {
			by_length[i] = new PairII(x2[i] - x1[i] + y2[i] - y1[i], i);
			if (x1[i] == x2[i]) {
				events.add(new Event(x1[i], 0, i));
			} else {
				events.add(new Event(x1[i], -1, i));
				events.add(new Event(x2[i], 1, i));
			}
		}
		Arrays.sort(by_length);
		Collections.sort(events);

		int crossings = 0;
		TreeMap<Integer, Integer> active = new TreeMap<Integer, Integer>();
		TreeMap<PairII, Integer> cross_xor = new TreeMap<PairII, Integer>();
		ArrayList<Integer>[] adj = new ArrayList[n];
		for (int i = 0; i < n; i++)
			adj[i] = new ArrayList<Integer>();
		for (Event e : events) {
			if (e.t == 0) {
				for (Entry<Integer, Integer> it = active.ceilingEntry(y1[e.i]); it != null
						&& it.getKey() <= y2[e.i]; it = active.higherEntry(it.getKey())) {
					adj[e.i].add(it.getValue());
					adj[it.getValue()].add(e.i);
					cross_xor.put(new PairII(e.x, it.getKey()), e.i ^ it.getValue());
					if (++crossings > 4 * n)
						return true;
				}
			} else if (e.t == -1) {
				active.put(y1[e.i], e.i);
			} else {
				active.remove(y1[e.i]);
			}
		}

		for (int flip = 0; flip < 2; flip++) {
			for (int i = 0; i < n; i++) {
				if (x1[i] == x2[i])
					continue;
				int y = y1[i];
				for (int above = 0; above < 2; above++) {
					Stack<PairII> stk = new Stack<PairII>();
					for (int j : adj[i]) {
						int x = x1[j];
						int h = above > 0 ? y2[j] - y : y - y1[j];
						while (!stk.isEmpty() && stk.peek().a < x)
							stk.pop();
						if (!stk.isEmpty()) {
							int k = stk.peek().b;
							int px = x1[k];
							int len = x - px;
							int py = y + (above > 0 ? len : -len);
							if (h >= len) {
								PairII p = new PairII(px, py);
								PairII q = new PairII(x, py);
								int l = -1;
								int m = -1;
								int bl = 0;
								int bm = 0;
								if (cross_xor.containsKey(p)) {
									l = k ^ cross_xor.get(p);
									bl = x2[l] - px;
								}
								if (cross_xor.containsKey(q)) {
									m = j ^ cross_xor.get(q);
									bm = x - x1[m];
								}
								if (longest_without(new int[] { i, j, k, l, m }) >= len - bl - bm)
									return true;
								if (longest_without(new int[] { i, j, k, l }) >= len - bl)
									return true;
								if (longest_without(new int[] { i, j, k, m }) >= len - bm)
									return true;
							}
						}
						stk.push(new PairII(h + x, j));
					}
				}
			}

			for (int i = 0; i < n; i++) {
				int tmp = y1[i];
				y1[i] = x1[i];
				x1[i] = tmp;

				tmp = y2[i];
				y2[i] = x2[i];
				x2[i] = tmp;
			}
			TreeMap<PairII, Integer> new_cross_xor = new TreeMap<PairII, Integer>();
			for (Entry<PairII, Integer> p : cross_xor.entrySet()) {
				new_cross_xor.put(new PairII(p.getKey().b, p.getKey().a), p.getValue());
			}
			cross_xor = new_cross_xor;
		}

		return false;
	}

	static int longest_without(int[] v) {
		for (int i = by_length.length - 1; i >= 0; i--) {
			boolean found = false;
			for(int j = 0; j < v.length; j++)
				if(by_length[i].b == v[j])
					found = true;
			if(!found)
				return by_length[i].a;
		}
		return 0;
	}
}

class PairII implements Comparable<PairII> {
	int a, b;

	public PairII(int a, int b) {
		this.a = a;
		this.b = b;
	}

	public int compareTo(PairII other) {
		if (other.a != a)
			return a - other.a;
		return b - other.b;
	}
}

class Event implements Comparable<Event> {
	int x, t, i;

	public Event(int x, int t, int i) {
		this.x = x;
		this.t = t;
		this.i = i;
	}

	public int compareTo(Event other) {
		if (other.x != x)
			return x - other.x;
		if(other.t != t)
			return t - other.t;
		return i - other.i;
	}
}
