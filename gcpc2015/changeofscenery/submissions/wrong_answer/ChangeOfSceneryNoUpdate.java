import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.TreeSet;

/* 
Common mistake for a dikstra implementation with java:
   uses dijkstra with a tree, update_key through changing the value of the object in the tree. 
   The mistake is, that the tree is not (automaticly) reodered after the update.
*/

public class ChangeOfSceneryNoUpdate {
	
	public static void main(String[] args)throws Exception{
        new ChangeOfSceneryNoUpdate().run();
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
	          int[][] states=new int[N][];

		  Arrays.fill(costs,Integer.MAX_VALUE);
		  //int[0] - Cost -> other information int[1]...int[?]
		  TreeSet<int[]> q=new TreeSet<int[]>(new Comparator<int[]>(){
			  public int compare(int[] a, int[] b){
				  if(a[0]<b[0]) return -1;
				  if(a[0]==b[0]) return a[1]-b[1];
				  return 1;
			  }
		  });
		  
                  states[start]=new int[]{0, start};
		  q.add(states[start]);
		  costs[start]=0;
		  cnts[start]=false;
		  while(! q.isEmpty()){
			  int[] akt=q.pollFirst();
			  int current=akt[1];
                	  if(current==goal) break;

			  for(Edge edge:graph[current]){
			    	   int nextCost=costs[current]+edge.weight;
			    	   /*Check: */
			    	   if(costs[edge.goal]<nextCost) continue;//
			    	   if(costs[edge.goal]==nextCost){
			    		   cnts[edge.goal]=true;
			    		   continue;
			    	   }
			    	   else
			    		   cnts[edge.goal]=cnts[current];
			    	   
			    	   int[] old=new int[]{costs[edge.goal], edge.goal};
			    	   q.remove(old);
			    	   
			    	   costs[edge.goal]=nextCost;
                                   if(states[edge.goal]==null){
			    	       states[edge.goal]=new int[]{nextCost, edge.goal};
                                       q.add(states[edge.goal]);
                                   }
				   else//just change the key:(wrong!)
                                      states[edge.goal][0]=nextCost;
		      }
		  }	
		  
		  return cnts[goal];
	}



}

