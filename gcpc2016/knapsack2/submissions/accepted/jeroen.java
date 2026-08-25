import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		String[] ps = in.readLine().split(" ");
		int N = Integer.valueOf(ps[0]);
		long K = Long.valueOf(ps[1]);
		long[] G = new long[N];
		ps = in.readLine().split(" ");
		for(int i = 0; i < N; i++)
			G[i] = Long.valueOf(ps[i]);

		// We can solve this modulo any of the items, lets use the last one
		// dp[i] = j means that j is smallest number we can make such that
		// i == j (mod G[N-1])
		long[] dp = new long[(int)G[N-1]];
		boolean[] done = new boolean[(int)G[N-1]];
		PriorityQueue<Long> Q = new PriorityQueue<Long>();
		Q.offer((long)0);
		while(!Q.isEmpty()) {
			long top = Q.poll();
			long topm = top % G[N-1];
			if(done[(int)topm]) continue;
			done[(int)topm] = true;
			dp[(int)topm] = top;
			for(int i = 0; i < N - 1; i++) {
				long next = top + G[i];
				long nextm = next % G[N-1];
				if(!done[(int)nextm])
					Q.offer(next);
			}
		}
		
		// Now if we can make K mod G[N-1] and it is at most K, we can
		// also make K (by adding multiples of G[N-1])
		if(done[(int)(K % G[N-1])] && dp[(int)(K % G[N-1])] <= K)
			System.out.println("possible");
		else
			System.out.println("impossible");
	}
}