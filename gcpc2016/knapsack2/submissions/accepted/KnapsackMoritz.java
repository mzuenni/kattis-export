import java.util.Arrays;
import java.util.PriorityQueue;
import java.util.Scanner;

public class KnapsackMoritz {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();
		long k = sc.nextLong();
		
		int[] g_array = new int[n];
		
		for(int i=0;i<n;i++) {
			g_array[i] = sc.nextInt();
		}
		
		Arrays.sort(g_array);
		int min_g = g_array[0];
		
		long[] dist = dijkstra(g_array, min_g);
		
		if(dist[(int)(k%min_g)] <= k) {
			System.out.println("possible");
		} else {
			System.out.println("impossible");
		}
		
	}
	
	public static long[] dijkstra(int[] g_array, int min_g) {
		PriorityQueue<Node> q = new PriorityQueue<Node>();
		q.add(new Node(0,0));
		
		long[] dist = new long[min_g];
		Arrays.fill(dist, Long.MAX_VALUE);
		dist[0] = 0;
		
		while(!q.isEmpty()) {
			Node n = q.poll();
			
			for(int i=1;i<g_array.length;i++) {
				int g = g_array[i];
				long distance = n.length + g;
				int next_node = (n.residual + g )%min_g;
				if(dist[next_node] > distance) {
					dist[next_node] = distance;
					q.add(new Node(next_node, distance));
				}
			}
		}
		
		return dist;
	}
	
	public static class Node implements Comparable<Node> {

		int residual;
		long length;
		
		public Node(int residual, long length) {
			this.residual = residual;
			this.length = length;
		}
		
		@Override
		public int compareTo(Node n) {
			if(n.length > this.length)
				return -1;
			if(n.length < this.length)
				return 1;
			return 0;
		}
		
	}

}
