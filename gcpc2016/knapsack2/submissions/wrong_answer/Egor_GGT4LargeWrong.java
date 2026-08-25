import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

/*

for K>G_max*G_max holds:
   K is reachable if and only if K%ggt(G_1, ..., G_max)==0

   Even more: per brute force, it can be shown, that for K>497_002  the ggt comparison is enough (if G_max<=1_000)

*/

public class Egor_GGT4LargeWrong {
	public static void main(String[] args)throws Exception{
        Scanner in=new Scanner(System.in);
        
        int N=in.nextInt();
        long K=in.nextLong();

        
        int[] gs=new int[N];  
        for(int i=0;i<N;i++)
        	gs[i]=in.nextInt();
        
        boolean loot = (K<497_002) ? bruteForce(gs, (int)K) : withGGT(gs, K);

        

        if(loot)
        	System.out.println("possible");
        else
        	System.out.println("impossible");
    }

  static boolean bruteForce(int[] gs, int K){
	boolean[] reachable=new boolean[K+1];
	reachable[0]=true;
	for(int g:gs)
           for(int i=0;i<=K;i++)
		if(reachable[i] && i+g<=K)
			reachable[i+g]=true;
	return reachable[K];
   }

  static boolean withGGT(int[] gs, long K){
	int ggt=gs[0];
	for(int i=1;i<gs.length;i++)
		ggt=GGT(ggt, gs[i]);
	return K%ggt==0;
   }

  static int GGT(int a, int b){
 	if(b == 0) return a;
	return GGT(b, a%b);
   }

}
