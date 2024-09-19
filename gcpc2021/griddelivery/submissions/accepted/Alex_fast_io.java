import java.io.*;
import java.util.*;

public class Alex_fast_io {
	
	public static PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
	
	private static class CustomScanner {
		BufferedReader br;
		StringTokenizer st;

		public CustomScanner() {
			br = new BufferedReader(new InputStreamReader(System.in));
		}

		String next() throws IOException {
			while(st == null || !st.hasMoreElements()) {
				st = new StringTokenizer(br.readLine());
			}
			return st.nextToken();
		}

		int nextInt() throws IOException {return Integer.parseInt(next()); }
	}

	private static class Column {
		private ArrayList<Integer> coins;

		public Column() {
			coins = new ArrayList<Integer>();
		}

		public void  Insert(int y) {
			coins.add(y);
		}

		public int Remove(int y) {
			int rm_pt = Collections.binarySearch(coins, y);
			if(rm_pt < 0) {
				rm_pt = -rm_pt - 1;
			}
			if(rm_pt < coins.size()) {
				y = coins.get(coins.size() - 1);
				coins.subList(rm_pt, coins.size()).clear();
			}
			return y;
		}

		public boolean isEmpty() {
			return coins.isEmpty();
		}
	}


	public static void main(String[] args) throws IOException {

		CustomScanner sc = new CustomScanner();
		int m = sc.nextInt(), n = sc.nextInt();
		ArrayList<Column> board = new ArrayList<Column>();
		for(int j = 0; j < n; ++j) {
			board.add(null);
		}
		for(int i = 0; i < m; ++i) {
			String line = sc.next();
			ListIterator<Column> it = board.listIterator();
			for(int j = 0; j < n; ++j) {
				it.next();
				if(line.charAt(j) == 'C') {
					Column col = board.get(j);
					if(col == null) {
						col = new Column();
						it.set(col);
					}
					col.Insert(i);
				}
			}
		}

		for(int j = 0; j < n; ++j) {
			Iterator<Column> it = board.iterator();
			while(it.hasNext()) {
				if(it.next() == null) {
					it.remove();
				}
			}
		}

		int runs = 0;
		while(!board.isEmpty()) {
			++runs;
			int y = 0;
			Iterator<Column> it = board.iterator();
			while(it.hasNext()) {
				Column col = it.next();
				y = col.Remove(y);
				if(col.isEmpty()) {
					it.remove();
				}
			}
		}
		out.println(runs);
		out.flush();
	}
}
