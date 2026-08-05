import java.util.*;


/*
 
 
 this solution imitates/is inspired by the usual dp solution (the whole calculation is modulo g[0])
 
 However, because we have not n but endless many items it is not so easy: we must calculate what happens
 if we add 1,2,3, and so on objects of the type i.
 
 So for N item types and g[0]=M we get O(N*M*M) running time.
 
 the program trys to change the order of the input, so it is always ascending
 
 */

public class EgorDPSortAscending {
	public static void main(String[] args)throws Exception{
	       Scanner in=new Scanner(System.in);
	        
	        int N=in.nextInt();
	        long K=in.nextLong();
	        
	        int[] gs=new int[N];
	        
	        for(int i=0;i<N;i++)
	        	gs[i]=in.nextInt();
	        
	        Arrays.sort(gs);//<--- here changing the order of elements
	        
	        int MAX=gs[0];

	        long[] minDists=getMinDists(gs, MAX);
	        
	        int index=(int)(K%MAX);
	        
	        if(minDists[index]<=K)
	        	System.out.println("possible");
	        else
	        	System.out.println("impossible");
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
