import java.util.Scanner;

public class SellingScannerMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		//int t = sc.nextInt();
		int t = 1;
		for(int tc=1;tc<=t;tc++) {
			int cpus = sc.nextInt();
			int merchants = sc.nextInt();
			
			long res = 0;
			long[][] prices = new long[merchants][cpus+1];
			long[][] dp = new long[merchants][cpus+1];
			
			
			for(int i=0;i<merchants;i++) {
				for(int j=1;j<=cpus;j++) {
					prices[i][j] = sc.nextInt();
				}
			}
			
			for(int i=0;i<merchants;i++) {
				dp[i][0] = 0;
			}
			
			for(int i=0;i<=cpus;i++) {
				dp[0][i] = prices[0][i];
			}
			
			for(int i=1;i<merchants;i++) {
				for(int j=0;j<=cpus;j++) {
					//value if we ignore merchant
					dp[i][j] = dp[i-1][j];
					//values if we sell some cpus to this merchant
					for(int k=1;k<=j;k++) {
						dp[i][j] = Math.max(dp[i][j] , dp[i-1][j-k] + prices[i][k]);
					}
				}
			}
			
			//Check for max result (max might not be at cpus CPUs!)
			for(int i=0;i<=cpus;i++) {
				res = Math.max(res , dp[merchants-1][i]);
			}
			
			//System.out.println("Case #" + tc + ": " + dp[merchants-1][cpus]);
			System.out.println(res);
		}
		
		
	}
	
}
