import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

public class RoutingMoritzBufferedReader {

	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(br.readLine());
		
		int[] time = new int[n]; 
		
		Set[] edges = new Set[n];
		
		for(int i=0;i<n;i++) {
			String in = br.readLine();
			String[] split = in.split(" ");
			int m = Integer.parseInt(split[0]);
			edges[i] = new HashSet<Vertex>();
			time[i] = Integer.parseInt(split[1]);
			for(int j=0;j<m;j++) {
				Set<Integer> blocked = new HashSet<Integer>();
				in = br.readLine();
				split = in.split(" ");
				int s = Integer.parseInt(split[0]);
				int x = Integer.parseInt(split[1])-1;
				
				for(int k=0;k<s;k++) {
					blocked.add(Integer.parseInt(split[k+2])-1);
				}
				edges[i].add(new Vertex(i,x,blocked));
			}
		}

		Vertex start = new Vertex(n+1,0,new HashSet<Integer>());
		PriorityQueue<Vertex> pq = new PriorityQueue<Vertex>();
		pq.add(start);
		start.distance = 0;
		
		while(!pq.isEmpty()) {
			Vertex v = pq.poll();
			
			if(v.to == n-1) {
				System.out.println(v.distance + time[n-1]);
				return;
			}
			
			for(Vertex to:(Set<Vertex>)edges[v.to]) {
				if(!to.blocked.contains(v.from)) {
					if(to.distance > v.distance + time[v.to]) {
						to.distance = v.distance + time[v.to];
						pq.remove(to);
						pq.add(to);
					}
				}
			}
		}
		
		System.out.println("impossible");
		
	}
	
	public static class Vertex implements Comparable<Vertex>{
		int distance;
		int from, to;
		Set<Integer> blocked;
		
		public Vertex(int from, int to, Set<Integer> blocked) {
			this.from = from;
			this.to = to;
			this.blocked = blocked;
			this.distance = Integer.MAX_VALUE;
		}
		
		@Override
		public int compareTo(Vertex v) {
			return distance - v.distance;
		}
	}
	

}
