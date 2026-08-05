import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;

public class ModelrailroadMoritzKruskal {

	public static void main(String[] args) throws IOException {	
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String in = br.readLine();
		String[] split = in.split(" ");
		
		int n = Integer.parseInt(split[0]);
		int m = Integer.parseInt(split[1]);
		int l = Integer.parseInt(split[2]);
		
		Set<Edge> nodes = new HashSet<Edge>();
		
		long max_size = 0;
		for(int i=0;i<m;i++) {
			in = br.readLine();
			split = in.split(" ");
			int from = Integer.parseInt(split[0])-1;
			int to = Integer.parseInt(split[1])-1;
			int length = Integer.parseInt(split[2]);
			
			if (i<l)
				max_size += length;
			nodes.add(new Edge(from,to,length));

		}
		
		long size = kruskal(n, nodes);
		
		//System.out.println(size);
		
		if(size == -1 || max_size < size) {
			System.out.println("impossible");
		} else {
			System.out.println("possible");
		}
		
	}
	
	public static long kruskal(int n, Set<Edge> nodes ) {
		
		long size = 0;
		
		PriorityQueue<Edge> pq = new PriorityQueue<Edge>();
		pq.addAll(nodes);
		
		UF uf = new UF(n);
		int unions = 0;
		while(!pq.isEmpty() && unions < n-1) {
			Edge e = pq.poll();
			int x = uf.find(e.from);
			int y = uf.find(e.to);
			if(x != y) {
				size += e.size;
				uf.union(e.from, e.to);
				unions++;
			}
		}
		
		if(unions < n-1)
			return -1;
		
		return size;
	}
	
	static class Edge implements Comparable<Edge>{
		int from, to;
		int size;
		
		public Edge(int from,  int to, int size) {
			this.from = from;
			this.to = to;
			this.size = size;
		}

		@Override
		public int compareTo(Edge e) {
			return this.size - e.size;
		}
	}
	
	static class UF {
		
		int[] parent;
		int[] size;
		
		public UF(int size) {
			this.parent = new int[size];
			this.size = new int[size]; 
			for(int i=0;i<size;i++) {
				this.parent[i] = i;
				this.size[i] = 1;
			}
		}
				
		public int find(int a) {
			if(parent[a] != a) {
				int ret = find(parent[a]);
				parent[a] = ret;
			}
			return parent[a];
		}
		
		public void union(int a, int b) {
			int x = find(a);
			int y = find(b);
			if(size[x] > size[y]) {
				parent[y] = x;
				size[x] += size[y];
			} else {
				parent[x] = y;
				size[y] += size[x];
			}
		}
	}
	
}
