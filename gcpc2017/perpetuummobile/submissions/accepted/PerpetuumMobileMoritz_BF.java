import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Scanner;

public class PerpetuumMobileMoritz_BF {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		sc.useLocale(Locale.US);
		
		int n = sc.nextInt();
		int m = sc.nextInt();
		
		HashMap<Integer,Double>[] g = new HashMap[n];
		double[] dist = new double[n];
		
		for(int i=0;i<n;i++) {
			g[i] = new HashMap<>();
		}
		
		for(int l=0;l<m;l++) {
			int a = sc.nextInt()-1;
			int b = sc.nextInt()-1;
			
			double c = Math.log(sc.nextDouble());
			if (g[a].containsKey(b)) {
				c = Math.max(g[a].get(b), c);
			}
			g[a].put(b, c);
		}
		
		boolean[] seen = new boolean[n];
		boolean res = false;
		
		for(int x=0; x<n&&!res;x++) {
		
			if (seen[x]) {
				continue;
			} 	
			Arrays.fill(dist, Double.MIN_VALUE);
			dist[x] = 0.0;
			for(int k : g[x].keySet()) {
				dist[k] = g[x].get(k); 
			}
			
			boolean change = true;
			int rounds = 0;
			while(change) {
				
				if (rounds > n) {
					res = true;
					break;
				}
				change = false;
				for(int start=0;start<n;start++) {
					
					for(int end : g[start].keySet()) {
						if(dist[end] < dist[start] + g[start].get(end)) {
							seen[end] = true;
							change = true;
							dist[end] = dist[start] + g[start].get(end);
						}
					}
					
				}
				rounds++;
			}
		}
		if (res) {
			System.out.println("inadmissible");
		} else {
			System.out.println("admissible");
		}
	}

}
