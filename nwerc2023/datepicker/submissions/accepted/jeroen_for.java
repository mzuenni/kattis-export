import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.math.*;

public class jeroen_for {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] agenda = new String[7];
		for(int i = 0; i < 7; i++)
			agenda[i] = in.readLine();
		String[] ps = in.readLine().split(" ");
		int d = Integer.valueOf(ps[0]);
		int h = Integer.valueOf(ps[1]);

		// Bruteforce the days and then sort the cols
		int best = 0;
		int[] bits = new int[7];
		for(bits[0] = 0; bits[0] <= 1; bits[0]++)
		for(bits[1] = 0; bits[1] <= 1; bits[1]++)
		for(bits[2] = 0; bits[2] <= 1; bits[2]++)
		for(bits[3] = 0; bits[3] <= 1; bits[3]++)
		for(bits[4] = 0; bits[4] <= 1; bits[4]++)
		for(bits[5] = 0; bits[5] <= 1; bits[5]++)
		for(bits[6] = 0; bits[6] <= 1; bits[6]++) {
			int nbits = bits[0] + bits[1] + bits[2] + bits[3] + bits[4] + bits[5] + bits[6];
			if(nbits != d) continue;

			ArrayList<Integer> cols = new ArrayList<Integer>();
			for(int j = 0; j < 24; j++) {
				int cur = 0;
				for(int k = 0; k < 7; k++)
					if(bits[k] > 0 && agenda[k].charAt(j) == '.')
						cur++;
				cols.add(cur);
			}
			Collections.sort(cols);
			Collections.reverse(cols);
			int sum = 0;
			for(int j = 0; j < h; j++)
				sum += cols.get(j);
			best = Math.max(best, sum);
		}

		System.out.println(best / (double)(h * d));
	}
}
