import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

/**
 * This is a slow solution for the knapsack problem. We use the classical approach
 * for the knapsack problem but compute everything modulo the lightest item.
 * Checking all possible improvements should be too slow.
 * 
 * @author Stefan Toman (toman@tum.de)
 */
public class StefanSlow {

	public static void main(String[] args) throws IOException {
		// read the input
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String[] nk = in.readLine().split(" ");
        int n = Integer.parseInt(nk[0]);
        long k = Long.parseLong(nk[1]);
        String[] tmp = in.readLine().split(" ");
        int[] g = new int[n];
        for (int i = 0; i < n; i++) {
			g[i] = Integer.parseInt(tmp[i]);
		}
        
        //sort weights
        Arrays.sort(g);
        
        //what can be done modulo g[0]?
        long[] min = new long[g[0]];
        Arrays.fill(min, Long.MAX_VALUE);
        min[0] = 0;
        for (int i = 1; i < n; i++) {
			boolean changed = false;
			for (int j = 0; j < g[0]; j++) {
				if(min[j] <= k && min[(j+g[i])%g[0]] > min[j]+g[i]) {
					min[(j+g[i])%g[0]] = min[j]+g[i];
					changed = true;
				}
			}
			if(changed) {
				i--;
			}
		}
        
        //output
        System.out.println(min[(int) (k%g[0])] <= k ? "possible" : "impossible");
	}
}
