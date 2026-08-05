import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;


public class BountyHunterEgorGreedy {
	public static void main(String[] args)throws Exception{
        new BountyHunterEgorGreedy().run();
    }
	
	Set<Integer>[] graph;

	
	@SuppressWarnings("unchecked")
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  
		  graph=new Set[N];
		  for(int i=0;i<N;graph[i++]=new HashSet<Integer>());
		  
		  
		  
		  for(int i=0;i<N;i++){
			  String[] goals=reader.readLine().split(" ");
			  for(int j=1;j<goals.length;j++)
				  graph[i].add(Integer.parseInt(goals[j]));
		  }
		  
		  System.out.println(findMinVisitorCnt());
	}
	
	int[] cnts;	
	boolean[] visited;
	
	int findMinVisitorCnt(){
		int N=graph.length;
		
		
		cnts=new int[N];
		visited=new boolean[N];
		
		for(Set<Integer> s:graph)
			for(int goal:s)
				cnts[goal]++;

		Queue<Integer> mustStartPoints=new LinkedList<Integer>();
		for(int i=0;i<N;i++)
			if(cnts[i]==0)
				mustStartPoints.offer(i);
		
		int res=0;
		while(!mustStartPoints.isEmpty()){
			int current=mustStartPoints.poll();
			
			if(visited[current])
				continue;
			res++;
			searchWay(current, mustStartPoints);
		}
		return res;
	}
	
	void searchWay(int current, Queue<Integer> mustStartPoints){
		visited[current]=true;
		
		int bestNext=-1;
		int minValue=Integer.MAX_VALUE;
		
		for(int next:graph[current]){
			if(visited[next])
				continue;
			if(cnts[next]<minValue){
				minValue=cnts[next];
				bestNext=next;
			}
			
			cnts[next]--;
			if(cnts[next]==0)
				mustStartPoints.offer(next);
		}
		
		if(bestNext!=-1)
			searchWay(bestNext, mustStartPoints);
	}
	
}
