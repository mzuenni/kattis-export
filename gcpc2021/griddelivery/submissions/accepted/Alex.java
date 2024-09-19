import java.util.*;

public class Alex {

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


	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
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
		sc.close();

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
		System.out.println(runs);
	}
}
