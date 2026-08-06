// @EXPECTED_RESULTS@: CORRECT
import java.util.*;
public class AlexTwoArrays{
	public static void main(String args[]){
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt(), T = 25000;
		int dp[] = new int[T+1];
		int ndp[] = new int[T+1];
		while(N-- > 0){
			int a = scan.nextInt(), b = scan.nextInt(), t = scan.nextInt();
			if(b > 0){
				for(int k = 0; true; ++k){
					int fun = a - b * k * k;
					if(fun < 0)break;
					for(int ct = 0; ct <= T; ct++){
						if(ct >= t)ndp[ct] = Math.max(dp[ct], dp[ct - t] + fun);
						else ndp[ct] = dp[ct];
					}
					int [] tmp = dp;
					dp = ndp;
					ndp = tmp;
					for(int j = 0; j <= T; j++)ndp[j] = 0;
				}
			} else {
				int fun = a;
				for(int ct = 0; ct <= T; ct++){
					if(ct >= t)ndp[ct] = Math.max(dp[ct], ndp[ct - t] + fun);
					else ndp[ct] = dp[ct];
				}
				int [] tmp = dp;
				dp = ndp;
				ndp = tmp;
				for(int j = 0; j <= T; j++)ndp[j] = 0;
			}
		}
		int Q = scan.nextInt();
		while(Q-->0){
			T = scan.nextInt();
			System.out.println(dp[T]);
		}
		System.exit(0);
	}
}
