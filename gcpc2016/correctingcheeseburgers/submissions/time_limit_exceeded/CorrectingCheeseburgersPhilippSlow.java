
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class CorrectingCheeseburgersPhilippSlow {
	
	static class CheeseBurger {
		
		public CheeseBurger(int[] order, int shuffles) {
			super();
			this.order = order;
			this.shuffles = shuffles;
		}

		int[] order;
		int shuffles;
		@Override
		public int hashCode() {
			// TODO Auto-generated method stub
			return Arrays.hashCode(order);
		}
		
		@Override
		public boolean equals(Object obj) {
			if (!(obj instanceof CheeseBurger)) {
				return false;
			}
			return Arrays.equals(order, ((CheeseBurger) obj).order);
		}
	}
	
	public static void main(String[] args) {
		FastScanner sc = new FastScanner(System.in);
		int n = sc.nextInt();
		int[] numbers = new int[n];
		for (int i = 0; i < numbers.length; i++) {
			numbers[i] = sc.nextInt();
		}
		// do a bfs
		Queue<CheeseBurger> q = new LinkedList<>();
		HashSet<CheeseBurger> reached = new HashSet<>();
		CheeseBurger cb = new CheeseBurger(numbers, 0);
		if (isSorted(cb)) {
			System.out.println(0);
			return;
		}
		q.add(cb);
		reached.add(cb);
		while (!q.isEmpty()) {
			cb = q.poll();
			// do the shuffles
			for (int a = 0; a <= n; a++) {
				for (int b = a; b <= n; b++) {
					for (int c = b; c <= n; c++) {
						CheeseBurger cb2 = shuffle(cb,a,b,c);
						if (isSorted(cb2)) {
							System.out.println(cb2.shuffles);
							return;
						}
						if (reached.contains(cb2)) {
							continue;
						}
						reached.add(cb2);
						q.add(cb2);
					}
				}
			}
		}
	}
	
	static CheeseBurger shuffle(CheeseBurger cb, int a, int b, int c) {
		CheeseBurger cb2 = new CheeseBurger(new int[cb.order.length],cb.shuffles+1);
		int pos = 0;
		//C
		for (int i = b; i < c; i++) {
			cb2.order[pos++] = cb.order[i];
		}
		//A
		for (int i = 0; i < a; i++) {
			cb2.order[pos++] = cb.order[i];
		}
		//D
		for (int i = c; i < cb.order.length; i++) {
			cb2.order[pos++] = cb.order[i];
		}
		//B
		for (int i = a; i < b; i++) {
			cb2.order[pos++] = cb.order[i];
		}
		return cb2;
	}
	
	static boolean isSorted(CheeseBurger cb) {
		for (int i = 0; i < cb.order.length - 1; i++) {
			if (cb.order[i] > cb.order[i+1]) {
				return false;
			}
		}
		return true;
	}
	
	static class FastScanner {
		BufferedReader br = null;
		StringTokenizer st = null;

		FastScanner(InputStream in) {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		public String next() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		public int nextInt() {
			return Integer.parseInt(next());
		}
		public double nextDouble() {
			return Double.parseDouble(next());
		}
	}

}
