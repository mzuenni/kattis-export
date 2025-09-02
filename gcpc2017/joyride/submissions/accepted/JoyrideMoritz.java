import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class JoyrideMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int x = sc.nextInt();
		int n = sc.nextInt();
		int m = sc.nextInt();
		int T = sc.nextInt();
		
		List<Integer>[] adj = new List[n];
		
		for(int i=0;i<n;i++) {
			adj[i] = new LinkedList<>();
		}
		
		for(int i=0;i<m;i++) {
			int start = sc.nextInt()-1;
			int end = sc.nextInt()-1;
			adj[start].add(end);
			adj[end].add(start);
		}

		int[] time = new int[n];
		int[] cost = new int[n];
		
		int[][] dp = new int[x+1][n];
		for(int i=0;i<n;i++) {
			time[i] = sc.nextInt();
			cost[i] = sc.nextInt();
			dp[0][i] = Integer.MAX_VALUE;
		}
		x -= time[0];
		dp[0][0] = 0;
		if (x < 0){
			System.out.println("It is a trap.");
			return;
		}
		// Figure out how much money we need to spend for time t ...
		for(int t=1;t<=x;t++) {
			// ... if we want to end up in a fixed state 
			for(int state=n-1;state>=0;state--) {
				if (t-time[state] < 0) {
					dp[t][state] = Integer.MAX_VALUE;
				} else {
					dp[t][state] = dp[t-time[state]][state]; 
					
					for (int neighbor : adj[state]) {
						// The current ride cost us time[state], let's see how much money we have to pay if we came from somewhere else
						if (t-time[state]-T >= 0)
							dp[t][state] = Math.min(dp[t][state] , dp[t-time[state]-T][neighbor]);
					}
					if (dp[t][state] != Integer.MAX_VALUE) {
						// Add cost if it is possible to reach the state in time t
						dp[t][state] += cost[state];
					}
				}
			}
		}
		// If it is possible to end up in state 0 with no time left output the needed amount of money
		if (dp[x][0] < Integer.MAX_VALUE) {
			System.out.println(dp[x][0] + cost[0]);
		} else {
			System.out.println("It is a trap.");
		}
	}
	
}
