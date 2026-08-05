import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;


public class LegacyCodeRecursiveMemEgor {

	public static void main(String[] args)throws Exception{
        new LegacyCodeRecursiveMemEgor().run();
    }
	
	
	private void run() throws Exception{
		  BufferedReader reader=new BufferedReader(new InputStreamReader(System.in));
		  
		  
		  int N=Integer.parseInt(reader.readLine());
		  
		  graph=new List[N];
		  for(int i=0;i<N;graph[i++]=new LinkedList<Integer>());
		  
		  
		  //fill the transposed graph:
		  MethodTracker tracker=new MethodTracker();
		  
		  for(int i=0;i<N;i++){
			  String[] description=reader.readLine().split(" ");
			  int goal=tracker.getIDforName(description[0]);
			  
			  String line=reader.readLine();
			  if(line.isEmpty())
				  continue;

			  String[] users=line.split(" ");

			  for(String user:users)
				  graph[goal].add(tracker.getIDforName(user));
		  }
		  
		  starts=tracker.getProgramIDs();
		  System.out.println(getUnusedCnt());
	}
	
	
	int[] used;
	List<Integer>[] graph;
	Set<Integer> starts;
	
	int getUnusedCnt(){
		
		int N=graph.length;
		int res=0;
		
		used=new int[N];
		for(int i=0;i<graph.length;i++){
			if(!isNeeded(i))
				res++;
		}
		
		return res;
	}
	
	boolean isNeeded(int i){
		if(used[i]!=0)
			return used[i]==2;
		
		if(starts.contains(i)){
			used[i]=2;
			return true;
		}
		else
			used[i]=1;

		
		for(int next:graph[i])
			 if(isNeeded(next)){
				 used[i]=2;
				 return true;
			 }
		
		return false;
	}
	
	private class MethodTracker{
		private Map<String, Integer> known;
		
		private Set<Integer> programIDs;
		
		Set<Integer> getProgramIDs(){
			return programIDs;
		}
		
		MethodTracker(){
			known=new HashMap<String, Integer>();
			programIDs=new HashSet<Integer>();
		}
		
		int getIDforName(String name){
			Integer index=known.get(name);
			int result=0;
			if(index==null){
				result=known.size();
				
				known.put(name, result);
				
				if(isPROGRAM(name))
					programIDs.add(result);
			}
			else{
				result=index;
			}
			
			return result;
		}
		
		private boolean isPROGRAM(String name){
			return name.endsWith("::PROGRAM");
		} 
	}

}
