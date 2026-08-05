import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Set;

public class ModelrailroadMoritzPrimInt {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String in = br.readLine();
		String[] split = in.split(" ");
		
		int n = Integer.parseInt(split[0]);
		int m = Integer.parseInt(split[1]);
		int l = Integer.parseInt(split[2]);
		
		List<Edge>[] graph = (List<Edge>[])new LinkedList[n];
		
		for(int i=0;i<n;i++) {
			graph[i] = new LinkedList<Edge>();
		}
		
		int max_size = 0;
		
		for(int i=0;i<m;i++) {
			in = br.readLine();
			split = in.split(" ");
			int from = Integer.parseInt(split[0])-1;
			int to = Integer.parseInt(split[1])-1;
			int length = Integer.parseInt(split[2]);
			
			if (i<l)
				max_size += length;
			
			graph[from].add(new Edge(from,to,length));
			graph[to].add(new Edge(to,from,length));
		}
		
		int size = mst_size(graph);
		
//		System.out.println(size);
		
		if(size == -1 || max_size < size) {
			System.out.println("impossible");
		} else {
			System.out.println("possible");
		}
		
		
	}
	
	public static int mst_size(List<Edge>[] graph) {
		
		Set<Integer> done = new HashSet<Integer>();
		PriorityQueue<Edge> q = new PriorityQueue<Edge>();
		
		for(Edge e: graph[0]) {
			q.add(e);
		}
		done.add(0);
		
		int ret = 0;
		while(done.size() < graph.length) {
			if(q.isEmpty())
				return -1;
			
			Edge e = q.poll();
			while(!q.isEmpty() && done.contains(e.to)) {
				e = q.poll();
			}
			if(e == null)
				return -1;
			
			done.add(e.to);
			
			ret += e.size;
			List<Edge> new_edges = graph[e.to];
			if(new_edges != null) {
				for(Edge ne:new_edges) {
					if(!done.contains(ne.to)) {
//						System.out.println("Adding " + e.from + " - " + e.to);
						q.add(ne);
					}
				}
			}
		}
		
		return ret;
	}
	
	public static class Edge implements Comparable<Edge>{
		public int size;
		public int from;
		public int to;
		
		public Edge(int from, int to, int size) {
			this.from = from;
			this.to = to;
			this.size = size;
		}
		
		@Override
		public int compareTo(Edge e) {
			return size - e.size;
		}
	}
	
}
