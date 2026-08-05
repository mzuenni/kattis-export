import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

/* uses dijkstra to count the number of shortest ways,but doesn't consider overflow */

public class ChangeOfSceneryCntInt {
	
	public static void main(String[] args)throws Exception{
        new ChangeOfSceneryCntInt().run();
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
		  
		  
		  
		  int res=dijkstra(graph, 0, N-1);
		  System.out.println(res==1? "no":"yes");
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

	int dijkstra(List<Edge>[] graph, int start, int goal){
		  int N=graph.length;
		  int[] costs=new int[N];
		  int[] cnts=new int[N];
		  boolean[] done=new boolean[N];
		  Arrays.fill(costs,Integer.MAX_VALUE);
		  //int[0] - Cost -> other information int[1]...int[?]
		  Queue<int[]> q=new PriorityQueue<int[]>(11,new Comparator<int[]>(){
			  public int compare(int[] a, int[] b){
				  if(a[0]<b[0]) return -1;
				  if(a[0]==b[0]) return 0;
				  return 1;
			  }
		  });
		  //costs[0][0]=0;
		  q.offer(new int[]{0, start});
		  costs[start]=0;
		  cnts[start]=1;
		  while(! q.isEmpty()){
			  int[] akt=q.poll();
			  int current=akt[1];
              if(current==goal) break;
			  if(done[current]) continue; //nicht aktuell
			  
			  done[current]=true;
			  for(Edge edge:graph[current]){
			    	   int nextCost=costs[current]+edge.weight;
			    	   /*Check: */
			    	   if(costs[edge.goal]<nextCost) continue;//
			    	   if(costs[edge.goal]==nextCost)
			    		   cnts[edge.goal]+=cnts[current];
			    	   else
			    		   cnts[edge.goal]=cnts[current];
			    	   
			    	   costs[edge.goal]=nextCost;
			    	   q.add(new int[]{nextCost, edge.goal});
		      }
		  }	
		  
		  return cnts[goal];
	}



}

