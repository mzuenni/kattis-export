import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;

public class DwarvesMoritz {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		String in = br.readLine();
		String[] split = in.split(" ");
		
		int t = Integer.parseInt(split[0]);
		HashMap<String, Vertex> graph = new HashMap<String,Vertex>();
		
		for(int i=0;i<t;i++) {
			in = br.readLine();
			split = in.split(" ");
			String from, to;
			if(split[1].equals("<")) {
				from = split[0];
				to = split[2];
			} else {
				from = split[2];
				to = split[0];
			}
			//System.out.println(from + " -> " + to);
			
			Vertex v = graph.get(from);
			if(v == null) {
				v = new Vertex(from);
				graph.put(from, v);
			}
			v.edges.add(new Edge(from,to));
		}
		
		HashSet<Vertex> done = new HashSet<Vertex>();
		for(Vertex v: graph.values()) {
			if(!done.contains(v)) {
				Stack<Vertex> s = new Stack<Vertex>();
				v.processing = true;
				s.push(v);
//				System.out.println("Start: " + v.name);
				
				while(!s.isEmpty()) {
					Vertex next = s.peek();
					next.processing = true;

//					System.out.println(next.name);
					
					if(next.iterator == null)
						next.iterator = next.edges.iterator();
					
					if(!next.iterator.hasNext()) {
						s.pop();
						next.processing = false;
					} else {
						Edge e = next.iterator.next();
						if(graph.get(e.to) != null && graph.get(e.to).processing) {
							System.out.println("impossible");
							return;
						}
						if(!done.contains(e.to)) {
							Vertex p = graph.get(e.to);
							if (p != null) {
								s.push(p);
								p.processing = true;
							}
							
						}
					}
					
					
				}
				done.add(v);
			}
		}
		System.out.println("possible");
		
		
	}
	
	public static class Vertex {
		String name;
		List<Edge> edges;
		Iterator<Edge> iterator = null;
		boolean processing = false;
		
		public Vertex(String name) {
			this.name = name;
			this.edges = new LinkedList<Edge>();
		}
	}
	
	public static class Edge {
		String from;
		String to;
		
		
		public Edge(String from, String to) {
			this.from = from;
			this.to = to;
		}
	}
	
}
