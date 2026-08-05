import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;
/*
 
 
 this solution imitates/is inspired by the usual dp solution (the whole calculation is modulo g[0])
 
 However, because we have not n but endless many items it is not so easy: we must calculate what happens
 if we add 1,2,3, and so on objects of the type i.
 
 So for N item types and g[0]=M we get O(N*M*M) running time.
 
 the program trys to change the order of the input, so it is always ascending modulo min value
 
 */

public class EgorDPSortPicking {
	public static void main(String[] args)throws Exception{
        Scanner in=new Scanner(System.in);
        
        int N=in.nextInt();
        long K=in.nextLong();
        
        int[] gs=new int[N];
        
        for(int i=0;i<N;i++)
        	gs[i]=in.nextInt();
        
        int MAX=pickMAX(gs);//be smart about the chose of MAX

        long[] minDists=getMinDists(gs, MAX);
        
        int index=(int)(K%MAX);
        if(minDists[index]<=K)
        	System.out.println("possible");
        else
        	System.out.println("impossible");
    }
	
	private static int pickMAX(int[] gs){
		Arrays.sort(gs);
		
		int MAX=gs[0];
		int n=gs.length;
		Pair[] pairs=new Pair[n-1];
		for(int i=1;i<n;i++)
			pairs[i-1]=new Pair(gs[i], MAX);
		
		Arrays.sort(pairs);
		for(int i=1;i<n;i++)
			gs[i]=pairs[i-1].g;
		
		return MAX;
	}
	
	static private class Pair implements Comparable<Pair>{
		int g;
		int gMod;
		Pair(int g, int MAX){
			this.g=g;
			this.gMod=g%MAX;
		}
		
		public int compareTo(Pair other){
			return gMod-other.gMod;
		}
	}

	
	
	static long[] getMinDists(int[] gs, int MAX){
		int n=gs.length;
		long[] dists=new long[MAX];
		Arrays.fill(dists, Long.MAX_VALUE);
		dists[0]=0L;
		for(int g:gs)
			for(int j=0;j<MAX;j++)
				if(dists[j]!=Long.MAX_VALUE){
					int current=j;
					while(true){
						int next=(current+g)%MAX;
						long nextValue=dists[current]+g;
						if(dists[next]<=nextValue)
							break;
						dists[next]=nextValue;
						current=next;
					}
				}
					
		  return dists;
	}
	
	
}
