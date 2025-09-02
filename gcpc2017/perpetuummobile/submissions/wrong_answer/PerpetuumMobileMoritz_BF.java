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
			double c = sc.nextDouble();
			if (g[a].containsKey(b)) {
				c = Math.max(g[a].get(b), c);
			}
			
			g[a].put(b, c);
		}
		
		Arrays.fill(dist, Double.MIN_VALUE);
		dist[0] = 1.0;
		for(int k : g[0].keySet()) {
			dist[k] = g[0].get(k); 
		}
		
		doIt(n, g, dist);
	}

	private static void doIt(int n, HashMap<Integer, Double>[] g, double[] dist) {
		boolean change = true;
		int rounds = 0;
		while(change) {
			//System.out.println("Case #" + tc + ": "+dist[0] + " " + dist[1]);
			rounds++;
			if (rounds >= n) {
				System.out.println("inadmissible");
				return;
			}
			change = false;
			for(int start=0;start<n;start++) {
				if (dist[start] > Double.MIN_VALUE) {
					for(int end : g[start].keySet()) {
						if(dist[end] < dist[start] * g[start].get(end)) {
							dist[end] = dist[start] * g[start].get(end);
							change = true;
						}
					}
				}
			}
		}
		
		System.out.println("admissible");
		return;
	}
	
	
}
