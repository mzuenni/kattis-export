import java.util.*;

public class Alex_no_fancy_stuff {

	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		int m = sc.nextInt(), n = sc.nextInt();
		ArrayList<ArrayList<Integer>> board = new ArrayList<ArrayList<Integer>>(n);
		for(int j = 0; j < n; ++j) {
			board.add(new ArrayList<Integer>(m));
		}
		for(int i = 0; i < m; ++i) {
			String line = sc.next();
			for(int j = 0; j < n; ++j) {
				if(line.charAt(j) == 'C') {
					board.get(j).add(i);
				}
			}
		}
		sc.close();

		int runs = -1;
		boolean has_coins = true;
		while(has_coins) {
			++runs;
			has_coins = false;
			int y = 0;
			for(int j = 0; j < n; ++j) {
				ArrayList<Integer> col = board.get(j);
				if(!col.isEmpty()) {
					has_coins = true;
					int new_y = col.get(col.size() - 1);
					if(new_y >= y) {
						while(!col.isEmpty() && col.get(col.size() - 1) >= y) {
							col.remove(col.size() - 1);
						}
						y = new_y;
					}
				}
			}
		}
		System.out.println(runs);
	}
}
