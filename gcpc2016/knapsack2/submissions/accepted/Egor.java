import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;


public class Egor {
	public static void main(String[] args)throws Exception{
        Scanner in=new Scanner(System.in);
        
        int N=in.nextInt();
        long K=in.nextLong();
        
        int[] gs=new int[N-1];
        
        int MAX=in.nextInt();
        
        for(int i=1;i<N;i++)
        	gs[i-1]=in.nextInt();
        
        long[] minDists=getMinDists(gs, MAX);
        
        int index=(int)(K%MAX);
        
        if(minDists[index]<=K)
        	System.out.println("possible");
        else
        	System.out.println("impossible");
    }
	
	static class Node implements Comparable<Node>{
		int pos;
		long value;
		Node(int pos, long value){
			this.pos=pos;
			this.value=value;
		}
		@Override
		public int compareTo(Node arg0) {
			if(value<arg0.value)
				return -1;
			if(value==arg0.value)
				return 0;
			return 1;
		}
		
		
	}
	
	
	static long[] getMinDists(int[] gs, int MAX){
		int n=gs.length;
		long[] dists=new long[MAX];
		Arrays.fill(dists, Long.MAX_VALUE);
		
		 Queue<Node> q=new PriorityQueue<Node>();
		 
		  q.offer(new Node( 0, 0L));
		  dists[0]=0L;
		  while(! q.isEmpty()){
			  Node cur=q.poll();
			  int current=cur.pos;
			  long curDist=cur.value;
			  if(curDist!=dists[current])
				  continue; //already processed
			  for(int edge:gs){
				  	   int next=(edge+current)%MAX;
			    	   long nextDist=curDist+edge;
			    	   if(dists[next]>nextDist){
			    		   dists[next]=nextDist;
				    	   q.add(new Node(next, nextDist));
			    	   }  
		      }
		  }	
		  return dists;
	}
	
	
}
