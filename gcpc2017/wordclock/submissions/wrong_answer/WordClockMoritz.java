import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class WordClockMoritz {

	private static class Fitting {
		int word = -1;
		int row = -1;
		int col = -1;
		Fitting prev = null;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int h = sc.nextInt();
		int w = sc.nextInt();
		int n = sc.nextInt();
		
		sc.nextLine();
		String[] words = new String[n]; 
		words = sc.nextLine().split(" ");
		
		List<String> actualWords = new LinkedList<>();
		// Throw away words that are subwords of other words
		for(int i=0;i<words.length;i++) {
			if(words[i].length() > w) {
				System.out.println("impossible");
				return;
			}
			boolean pick = true;
			for(int j=0;j<words.length;j++) {
				if (i != j && words[j].contains(words[i])) {
					pick = false;
					break;
				}
			}
			if(pick) {
				actualWords.add(words[i]);
			}
		}
		
		n = actualWords.size();
		words = actualWords.toArray(new String[actualWords.size()]);
		
		// How much space do we need to print word i followed by word j?
		int[][] dist = new int[n][n];
		
		
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				if(i!=j) {
					dist[i][j] = 0;
					// No need to check for end of words, since we filtered out words that are subwords of other words.
					while(words[i].substring(words[i].length() - dist[i][j]).equals(words[j].substring(0, dist[i][j]))) {
						dist[i][j]++;
					}
					dist[i][j]--;
					dist[i][j] = words[j].length() - dist[i][j]; 
				}
			}
		}
		
		// DP-entries: (subset of words X last used word) -> space we need to place subset of words with specified last word.
		Fitting[][] dp = new Fitting[1<<n][n];
		
		// If we only use one word, we need know how much space we need.
		for(int i=0; i<n;i++) {
			dp[1<<i][i] = new Fitting();
			dp[1<<i][i].word = i; 
			dp[1<<i][i].row = 1; 
			dp[1<<i][i].col = words[i].length();
			dp[1<<i][i].prev = null; 
		}
		
		//Go through all subsets except the empty set
		for(int set=3;set<= (1<<n)-1;set++) {
			// Place all possible words as last word
			for(int itemA=0;itemA<n;itemA++) {
				if ((1<<itemA & set) > 0) {
					// itemA is in the current subset
					for(int itemB=0;itemB<n;itemB++) {
						if (itemA != itemB && (1<<itemB & set) > 0) {
							// itemB is in the current subset and we want to place it last.

							if (dp[set ^ 1<<itemB][itemA] == null) {
								continue;
							}
							//Figure out how much extra space we need for that
							int row = dp[set ^ 1<<itemB][itemA].row;
							int col = dp[set ^ 1<<itemB][itemA].col;
							if (col + dist[itemA][itemB] > w) {
								row++;
								col = words[itemB].length();
							} else {
								col += dist[itemA][itemB];
							}
							// If we need more height than we have we don't have to remember.
							if(row > h) {
								continue;
							}
							
							// Update dp array
							if (dp[set][itemB] == null) {
								dp[set][itemB] = new Fitting();
								dp[set][itemB].word = itemB;
								dp[set][itemB].row = row;
								dp[set][itemB].col = col;
								dp[set][itemB].prev = dp[set ^ (1<<itemB)][itemA];
							} else {
								if (row < dp[set][itemB].row || (row == dp[set][itemB].row && col < dp[set][itemB].col)) {
									dp[set][itemB].row = row;
									dp[set][itemB].col = col;
									dp[set][itemB].prev = dp[set ^ (1<<itemB)][itemA];
								}
							}
						}
					}
				}
			}
		}
		
		Fitting fitting = null;
		for(int i=0;i<n;i++) {
			
			//System.out.println(dp[(1<<n)-1][i].row + " " + dp[(1<<n)-1][i].col + " " + words[dp[(1<<n)-1][i].word]);
			
			// We WIN!
			if (dp[(1<<n)-1][i] != null && dp[(1<<n)-1][i].row <= h) {
				fitting = dp[(1<<n)-1][i];
				break;
			}
		}
		
		if(fitting==null) {
			System.out.println("impossible");
			return;
		} else {
			// We still need to puzzle the actual result back together
			String[] clock = new String[h];
			Arrays.fill(clock, String.join("", Collections.nCopies(w, "X")));
			while (fitting != null) {
				String nw = clock[fitting.row-1].substring(0, fitting.col- words[fitting.word].length());
				nw += words[fitting.word];
				nw += clock[fitting.row-1].substring(fitting.col);
				clock[fitting.row-1] = nw;
				fitting = fitting.prev;
			} 
			for(String s: clock) {
				System.out.println(s);
			}			
		}

	}

}
