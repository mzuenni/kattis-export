import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.TreeMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;


public class BountyHunterMaxFlowEgor {
	
	public static void main(String[] args)throws Exception{
        new BountyHunterMaxFlowEgor().run();
    }
	

	@SuppressWarnings("unchecked")
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  int graphSize=2*N+2;
		  Map<Integer, Integer>[] graph=new Map[graphSize];
		  for(int i=0;i<graphSize;i++)
			graph[i]=new TreeMap<Integer, Integer>();
			
		  for(int i=0;i<N;i++){
			  graph[graphSize-2].put(i,1);
			  graph[N+i].put(graphSize-1, 1);
		  }

		  for(int i=0;i<N;i++){
			  String[] goals=reader.readLine().split(" ");
			  for(int j=1;j<goals.length;j++){
				  int currentGoal=Integer.parseInt(goals[j]);
				  graph[i].put(N+currentGoal,1);
			  }
		  }
		  
		  System.out.println(N-maxFlow(graph, graphSize-2, graphSize-1));
	}

	
	int maxFlow(Map<Integer, Integer>[]graph, int source, int target){
		int res=0;
		int N=graph.length;
		
		while(true){
			//suche einen weg von s nacht t via bfs
			int[] vor=new int[N];
			Arrays.fill(vor, -1); //vor==-1, falls der Knoten nocht nicht besucht
			Queue<Integer> q=new LinkedList<Integer>();
			q.offer(source);
			vor[source]=-2; //Source ist die Quelle!
			bfs: while(! q.isEmpty()){
				int akt=q.poll();
				Set<Integer> keys=graph[akt].keySet();
				for(int next:keys)
						if(vor[next]==-1){
							vor[next]=akt;
							if(next==target) break bfs; //Early exit
							q.offer(next);
						}
			}
			if(vor[target]==-1) break; //Keine Vebesserung mehr moeglich
			
			//Setze den Weg zusammen, merke dabei das Minimum:
			List<Integer> way=new LinkedList<Integer>();
			int min=Integer.MAX_VALUE;
			int akt=target;
			way.add(0, target);
			while(true){
				int next=vor[akt];
				if(next==-2) break; //source gefunden!
				min=Math.min(min, graph[next].get(akt));
				way.add(0, next);
				akt=next;
			}
			
			//Nun drehe die Kanten um:
			akt=-1;
			for(int next:way){
				if(akt!=-1){
					//verkleine hinrichtung:
					Integer w=graph[akt].remove(next);
					int newW=w-min;
					if(newW>0) graph[akt].put(next, newW);
					//vergroessere rueckrichtung
					w=graph[next].get(akt);
					newW=(w==null)?min:w+min;
					graph[next].put(akt, newW);
				}
				akt=next;
			}
			
			//Aktualisiere den Fluss:
			res+=min;
			
		}
		
		return res;
	}
	
	
}
