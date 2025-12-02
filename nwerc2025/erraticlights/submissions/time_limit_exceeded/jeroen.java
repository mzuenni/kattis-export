import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	static int k = 3;

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		char[] t = in.readLine().trim().toCharArray();

		// Construct initial counts
		TreeMap<Character, Integer> counts = new TreeMap<>();
		for (int i = 0; i < n; i++) {
			if(counts.containsKey(t[i]))
				counts.put(t[i], counts.get(t[i]) + 1);
			else
				counts.put(t[i], 1);
		}
		SlimeCounts initial = new SlimeCounts(counts.values().stream().sorted().mapToInt(i->i).toArray());
		System.out.println(recurse(initial));
	}

	static HashMap<SlimeCounts, Double> cache = new HashMap<>();
	public static double recurse(SlimeCounts cur) {
		// base case, only 1 type remaining
		if(cur.size() == 1) {
			return 0;
		}
		if(cache.containsKey(cur))
			return cache.get(cur);

		int m = cur.size();
		// for m-1 results we recurse, for the rest of the k-(m-1)
		// outcomes we keep clicking the same slime, so we stay in
		// this state. So if x is the expected clicks of this state,
		// then we have
		// x = 1 + 1/k r_1 + 1/k r_2 ... 1/k r_(m-1) + (k-(m-1))/k x
		// (m-1)/k x = 1 + 1/k (r_1 + r_2 ... r_(m-1))
		// (m-1) x = k + r_1 + r_2 ... r_(m-1)
		// x = (k + r_1 + r_2 ... r_(m-1)) / (m-1)
		double answer = k;
		SlimeCounts c = cur.removeFirst();
		for(int i = 0; i < m - 1; i++) {
			answer += recurse(c.addOne(c.size()-i-1));
		}
		answer /= (m-1);

		cache.put(cur, answer);
		return answer;
	}
}

// sorted set with counts
class SlimeCounts {
	int[] counts;

	public SlimeCounts(int[] counts) {
		this.counts = counts;
	}

	public int size() {
		return counts.length;
	}

	public SlimeCounts removeFirst() {
		int n = counts[0] == 1 ? counts.length - 1 : counts.length;
		int[] ncounts = new int[n];
		for(int j = 0; j < n; j++)
			ncounts[j] = counts[counts[0] == 1 ? j + 1 : j];
		if(counts[0] > 1)
			ncounts[0]--;

		return new SlimeCounts(ncounts);
	}

	public SlimeCounts addOne(int i) {
		int[] cp = new int[this.size()];
		for(int j = 0; j < cp.length; j++)
			cp[j] = counts[j];
		while(i < counts.length - 1 && cp[i+1] == cp[i])
			i++;
		cp[i]++;
		return new SlimeCounts(cp);
	}
}
