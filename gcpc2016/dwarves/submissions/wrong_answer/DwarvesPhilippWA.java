import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;

// will report a cycle in some cases when there is none
// e.g. if there is a triangle 1->2->3 and 1->3
// (and the edges are processed in that order)
public class DwarvesPhilippWA {

	static class Node {
		public HashSet<Edge> edges = new HashSet<>();
		boolean onStack = false;
		boolean done = false;
	}

	static class Edge {
		Node end;
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int number = Integer.parseInt(sc.nextLine().split(" ")[0]);
		Map<String, Node> map = new HashMap<>();
		for (int i = 0; i < number; i++) {
			String[] line = sc.nextLine().split(" ");
			Node n1 = map.get(line[0]);
			if (n1 == null) {
				n1 = new Node();
				map.put(line[0], n1);
			}
			Node n2 = map.get(line[2]);
			if (n2 == null) {
				n2 = new Node();
				map.put(line[2], n2);
			}
			Edge edge = new Edge();
			if (line[1].equals("<")) {
				edge.end = n1;
				n2.edges.add(edge);
			} else {
				edge.end = n2;
				n1.edges.add(edge);
			}
		}
		// find cycles
		for (Node start : map.values()) {
			if (!start.done) {
				// launch dfs from n
				Stack<Node> s = new Stack<>();
				s.push(start);
				start.onStack = true;
				while (!s.isEmpty()) {
					Node n = s.peek();
					s.pop();
					n.onStack = false;
					n.done = true;
					for (Edge e : n.edges) {
							if (e.end.onStack || e.end.done) {
								System.out.println("impossible");
								return;
							}
							if (!e.end.done){
							    s.push(e.end);
							    e.end.onStack = true;
							}
					}
				}
			}
		}
		System.out.println("possible");

	}
}
