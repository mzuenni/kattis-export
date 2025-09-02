import java.util.Arrays;
import java.util.HashMap;
import java.util.Locale;
import java.util.Scanner;

public class PerpetuumMobileMoritz_FW_noLog {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		sc.useLocale(Locale.US);
		
		int n = sc.nextInt();
		int m = sc.nextInt();
		
		HashMap<Integer,Double>[] g = new HashMap[n];
		double[][] dist = new double[n][n];
		
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
			dist[a][b] = c;
		}
		
		doIt(n, g, dist);
	}

	private static void doIt(int n, HashMap<Integer, Double>[] g, double[][] dist) {
		
		for(int start=0;start<n;start++) {
			for(int mid=0;mid<n;mid++) {
				for(int end=0;end<n;end++) {
					if (dist[start][end] < dist[start][mid] * dist[mid][end]) {
						if (start == end && dist[start][mid] * dist[mid][end] > 1.0) {
							System.out.println("inadmissible");
							return;
						}
						
						dist[start][end] = dist[start][mid] * dist[mid][end];
					}
				}
			}
		}
		System.out.println("admissible");
	}
	
	
}

