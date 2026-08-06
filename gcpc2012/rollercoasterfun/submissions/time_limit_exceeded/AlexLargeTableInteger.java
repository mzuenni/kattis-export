// @EXPECTED_RESULTS@: TIMELIMIT
import java.util.*;
public class AlexLargeTableInteger{
	static int itemProfit[], itemSize[];
	static boolean itemInfinity[];
	static Integer dp[][];
	
	public static int rek(int id, int t){
		if(t < 0) return -1000000000;
		if(id == -1)return 0;
		if(dp[id][t] == null){
			if(itemInfinity[id])dp[id][t] = rek(id    , t - itemSize[id]) + itemProfit[id];
			else 				dp[id][t] = rek(id - 1, t - itemSize[id]) + itemProfit[id];
			dp[id][t] = Math.max(dp[id][t], rek(id - 1, t));
		}
		return dp[id][t];
	}
	public static void main(String args[]){
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt(), T = 25000, J = 0;
		itemProfit = new int[N*40];
		itemSize = new int[N*40];
		itemInfinity = new boolean[N*40];
		while(N-- > 0){
			int a = scan.nextInt(), b = scan.nextInt(), t = scan.nextInt();
			if(b > 0){
				for(int k = 0; true; ++k){
					int fun = a - b * k * k;
					if(fun < 0)break;
					itemProfit[J] = fun;
					itemSize[J] = t;
					itemInfinity[J++] = false;
				}
			} else {
				itemProfit[J] = a;
				itemSize[J] = t;
				itemInfinity[J++] = true;
			}
		}
		dp = new Integer[J][T+1];
		for(int i = 0; i < J; i++)
			for(int t = 0; t <= T; t++)rek(i, t);
		int Q = scan.nextInt();
		while(Q-->0){
			T = scan.nextInt();
			System.out.println(rek(J-1,T));
		}
		System.exit(0);
	}
}
