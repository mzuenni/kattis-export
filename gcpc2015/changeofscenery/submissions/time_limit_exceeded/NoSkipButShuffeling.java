import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Collections;

/* 
Common mistake for a dikstra implementation with java:
   uses dijkstra with java priority queue, update key through inserting a new value,
   however the old values in queue are not skipped (as they should be) leading to O(N*M) in the worst case 

Trying to trick the handmade test cases by shuffeling
*/

public class NoSkipButShuffeling {
	
	public static void main(String[] args)throws Exception{
        new NoSkipButShuffeling().run();
    }
	
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  String[] nmk=reader.readLine().split(" ");
		  int N=Integer.parseInt(nmk[0]);
		  int M=Integer.parseInt(nmk[1]);
		  
//skipp the line:
		  reader.readLine();
		  
		  graph=inizializeGraph(N);

		  for(int i=0;i<M; i++){
			  String[] stw=reader.readLine().split(" ");
			  int source=Integer.parseInt(stw[0])-1;
			  int target=Integer.parseInt(stw[1])-1;
			  int weight=Integer.parseInt(stw[2]);
			  
			  graph[source].add(new Edge(target, weight));
			  graph[target].add(new Edge(source, weight));
		  }
		  
		  shuffle(graph);
		  
		  boolean res=dijkstra(graph, 0, N-1);
		  System.out.println(res? "yes":"no");
	}
	
	List<Edge>[] inizializeGraph(int N){
		@SuppressWarnings("unchecked")
		List<Edge>[] graph=new List[N];
		for(int i=0;i<N;i++)
			graph[i]=new LinkedList<Edge>();
		return graph;
	}

	void shuffle(List<Edge>[] graph){
		for(List<Edge> nexts: graph)
			Collections.shuffle(nexts);//Every line I'm shuffeling
	}
	
	List<Edge>[] graph;
	
    public class Edge{
		public int weight;
		public int goal;
		
		public Edge(int goal, int weight){
			this.weight=weight;
			this.goal=goal;
		}
	}

	boolean dijkstra(List<Edge>[] graph, int start, int goal){
		  int N=graph.length;
		  int[] costs=new int[N];
		  boolean[] cnts=new boolean[N];

		  Arrays.fill(costs,Integer.MAX_VALUE);
		  //int[0] - Cost -> other information int[1]...int[?]
		  Queue<int[]> q=new PriorityQueue<int[]>(11,new Comparator<int[]>(){
			  public int compare(int[] a, int[] b){
				  if(a[0]<b[0]) return -1;
				  if(a[0]==b[0]) return 0;
				  return 1;
			  }
		  });

		  q.offer(new int[]{0, start});
		  costs[start]=0;
		  cnts[start]=false;
		  while(! q.isEmpty()){
			  int[] akt=q.poll();
			  int current=akt[1];
                	  if(current==goal) break;
			  //you should skip the current here if it has been already proceded, but you don't
			  for(Edge edge:graph[current]){
			    	   int nextCost=akt[0]+edge.weight;
			    	   /*Check: */
			    	   if(costs[edge.goal]<nextCost) continue;//
			    	   if(costs[edge.goal]==nextCost){
			    		   cnts[edge.goal]=true;
                                           continue;
                                   }
			    	   
				   cnts[edge.goal]=cnts[current];
			    	   costs[edge.goal]=nextCost;
			    	   q.add(new int[]{nextCost, edge.goal});
		      }
		  }	
		  
		  return cnts[goal];
	}



}

