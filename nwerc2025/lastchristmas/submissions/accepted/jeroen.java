import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		String[][] lists = new String[n][10];
		for(int i = 0; i < n; i++)
			lists[i] = in.readLine().split(" ");

		// Do some counting
		TreeSet<String> artists = new TreeSet<String>();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < 10; j++)
				artists.add(lists[i][j]);
		int m = artists.size();
		// counts[i][0] is total appearances, counts[i][1..10] are counts per position
		List<Object> artista = Arrays.asList(artists.toArray());
		int[][] counts = new int[m][11];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < 10; j++) {
				int k = artista.indexOf(lists[i][j]);
				counts[k][0]++;
				counts[k][j+1]++;
			}
		}

		// Now find the best one
		int best = 0;
		boolean tie = false;
		for(int i = 1; i < m; i++) {
			if(Arrays.compare(counts[i], counts[best]) > 0) {
				best = i;
				tie = false;
			} else if(Arrays.compare(counts[i], counts[best]) == 0) {
				tie = true;
			}
		}

		if(tie) System.out.println("tie");
		else System.out.println(artista.get(best));
	}
}
