import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.math.*;

public class jeroen {
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
		for(int i = 0; i < (1<<7); i++) {
			int bits = 0;
			for(int j = 0; j < 7; j++)
				if((i & (1<<j)) > 0)
					bits++;
			if(bits != d) continue;

			ArrayList<Integer> cols = new ArrayList<Integer>();
			for(int j = 0; j < 24; j++) {
				int cur = 0;
				for(int k = 0; k < 7; k++)
					if((i & (1<<k)) > 0 && agenda[k].charAt(j) == '.')
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
