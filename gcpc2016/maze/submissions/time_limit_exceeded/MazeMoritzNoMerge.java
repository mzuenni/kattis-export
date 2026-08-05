import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class MazeMoritzNoMerge {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		double eps = 10e-7;
		
		int n = sc.nextInt();
		int m = sc.nextInt();
		
		Vertex[] vertices = new Vertex[n+1];
		
		for(int i=1;i<=n;i++) {
			vertices[i] = new Vertex();
		}
		
		for(int i=0;i<m;i++) {
			int from = sc.nextInt();
			int to = sc.nextInt();
			Character c = sc.next().charAt(0);
			List<Integer> list = vertices[from].transitions.get(c);
			if(list == null) {
				list = new LinkedList<Integer>();
				vertices[from].transitions.put(c, list);
			}
			list.add(to);
			
			list = vertices[to].transitions.get(c);
			if(list == null) {
				list = new LinkedList<Integer>();
				vertices[to].transitions.put(c, list);
			}
			list.add(from);
		}
		
		char[] in = sc.next().toCharArray();
		
		List<Run> runs = new LinkedList<Run>();
		runs.add(new Run(1,1.0));
		for(char c: in) {
			List<Run> new_runs = new LinkedList<Run>();
			for(Run r:runs) {
				List<Integer> transitions = vertices[r.vertex].transitions.get(c);
				if(transitions == null || r.vertex == n) {
					new_runs.add(r);
					continue;
				}
				for(Integer to : transitions) {
					new_runs.add(new Run(to,r.prob / transitions.size()));
				}
			}
			runs = new_runs;
		}
		
		double result = 0.0;
		for(Run r: runs) {
			if(r.vertex == n)
				result += r.prob;
		}
		result = 100*result;
		
		System.out.println(result);
		
	}
	
	private static class Run {
		Integer vertex;
		Double prob;

		public Run(Integer vertex, Double prob) {
			this.vertex = vertex;
			this.prob = prob;
		}
	}
	
	private static class Vertex {
		Map<Character, List<Integer>> transitions = new HashMap<Character,List<Integer>>();
	}
	
}
