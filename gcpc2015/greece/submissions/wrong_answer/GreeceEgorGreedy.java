import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Set;
import java.util.TreeSet;

/*
 * uses a kind of kruskal to solve TSP in greedy fashion
 * 
 * 
 */

public class GreeceEgorGreedy {

	
	public static void main(String[] args) throws Exception{
        new GreeceEgorGreedy().run();
    }

	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
			  solveTestCase(reader);
	}
	
	
	void solveTestCase(BufferedReader reader) throws Exception{
		  String[] npmgt=reader.readLine().split(" ");
		  int N=Integer.parseInt(npmgt[0]);
		  int P=Integer.parseInt(npmgt[1]);
		  int M=Integer.parseInt(npmgt[2]);
		  int G=Integer.parseInt(npmgt[3]);
		  int T=Integer.parseInt(npmgt[4]);
		  
		  int additionalTime=0;
		  Set<Integer> placesToVisit=new TreeSet<Integer>();
		  placesToVisit.add(0);//start in Athen
		  for(int i=0;i<P;i++){
			  String[] place=reader.readLine().split(" ");
			  placesToVisit.add(Integer.parseInt(place[0]));
			  additionalTime+=Integer.parseInt(place[1]);
		  }
		  
		  List<int[]>[] graph=new List[N];
		  for(int i=0;i<N;i++)
			  graph[i]=new LinkedList<int[]>();
		  
		  for(int i=0;i<M;i++){
			  String[] edge=reader.readLine().split(" ");
			  int from=Integer.parseInt(edge[0]);
			  int to=Integer.parseInt(edge[1]);
			  int w=Integer.parseInt(edge[2]);
			  graph[from].add(new int[]{w,to});
			  graph[to].add(new int[]{w,from});
		  }
		 
		  int[][] dists=reduceGraph(graph, placesToVisit);
		  
		  int[] way=getTSPWay(dists);
		  int timeWithoutTaxi=0;
		  for(int i:way)
			  timeWithoutTaxi+=i;
		  
		  
		  if(timeWithoutTaxi+additionalTime<=G){
			  System.out.println("possible without taxi");
			  return;
		  }
		  
		  int timeWithTaxi=timeWithoutTaxi-way[way.length-1]+T;
		  if(timeWithTaxi+additionalTime<=G)
			  System.out.println("possible with taxi");
		  else
			  System.out.println("impossible"); 
			  
	}
	
	
	int[][] reduceGraph(List<int[]>[] graph, Set<Integer> places){
		int n=places.size();
		int[][] result=new int[n][n];
		int ind1=0;
		for(int start:places){
			int[] dists=dijkstra(graph, start);
			int ind2=0;
			for(int end:places)
				result[ind1][ind2++]=dists[end];
			
			ind1++;
		}
		return result;
	}
	
	
	int[] dijkstra(List<int[]>[] graph, int start){
		  int N=graph.length;
		  int[] dists=new int[N];
		  Arrays.fill(dists,Integer.MAX_VALUE);
		  //int[0] - weight -> other information int[1]...int[?]
		  Queue<int[]> q=new PriorityQueue<int[]>(11,new Comparator<int[]>(){
			  public int compare(int[] a, int[] b){
				  if(a[0]<b[0]) return -1;
				  if(a[0]==b[0]) return 0;
				  return 1;
			  }
		  });
		  //costs[0][0]=0;
		  q.offer(new int[]{0, start});
		  dists[start]=0;
		  while(! q.isEmpty()){
			  int[] akt=q.poll();
			  int current=akt[1];
			  int curDist=akt[0];
			  if(curDist!=dists[current]) continue; //already processed
			  for(int[] edge:graph[current]){
				  	   int next=edge[1];
			    	   int nextDist=dists[current]+edge[0];
			    	   if(dists[next]>nextDist){
			    		   dists[next]=nextDist;
				    	   q.add(new int[]{nextDist, next});
			    	   }  
		      }
		  }	
		  return dists;
	}
	
	
 class Edge implements Comparable<Edge>{
	 int from;
	 int to;
	 int weight;
	 public int compareTo(Edge other){
		 return this.weight-other.weight;
	 }
	 
	 Edge(int from, int to, int w){
		 this.from=from;
		 this.to=to;
		 this.weight=w;
	 }
 }
  int[] getTSPWay(int[][] dists){
	 int n=dists.length;
	 
	 if(n==2){ 
		 int[] res=new int[2];
		 res[0]=dists[0][1];
		 res[1]=dists[1][0];
		 return res;
	 }
	 
	 Edge[] edges=new Edge[n*(n-1)/2];
	 int cnt=0;
	 for(int i=0;i<n;i++)
		 for(int j=i+1;j<n;j++)
			 edges[cnt++]=new Edge(i,j, dists[i][j]);
	 Arrays.sort(edges);
	 int[] cnts=new int[n];
	 int[] way=new int[n];
	 int currentSegment=0;
	 
	 for(Edge edge:edges){
		 if(cnts[edge.from]!=2 && cnts[edge.to]!=2){
			 way[currentSegment++]=edge.weight;
			 cnts[edge.from]++;
			 cnts[edge.to]++;
		 }
	 }

	 
	 return way;
  }

}


