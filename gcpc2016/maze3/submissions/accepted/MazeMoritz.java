import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

public class MazeMoritz {

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
		
		double[] prob = new double[n+1];
		prob[1] = 1.0;
		
		
		Set<Integer> runs = new HashSet<Integer>();
		runs.add(1);
		for(char c: in) {
			Set<Integer> new_runs = new HashSet<Integer>();
			double[] newprob = new double[n+1];
			for(int r:runs) {
				List<Integer> transitions = vertices[r].transitions.get(c);
				if(transitions == null || r == n) {
//					System.out.println(newprob[r]);
					newprob[r] += prob[r];
					new_runs.add(r);
				} else {
					for(Integer to : transitions) {
						newprob[to] += prob[r] / transitions.size();
						if(!new_runs.contains(to)) {
							new_runs.add(to);
						}
					}
				}
			}
			runs = new_runs;
			prob = newprob;
		}
		
		double result = 100*prob[n];
		
//		System.out.println(prob[n]);
		
		if(result > 0.0) {
			System.out.println(result);
		} else {
			System.out.println("0.0");
		}
		
	}
	
	private static class Vertex {
		Map<Character, List<Integer>> transitions = new HashMap<Character,List<Integer>>();
	}
	
}
