import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;
import java.util.StringTokenizer;

public class PlugItInMoritzHopcroftKarp {

	static ArrayList<Integer>[] adj;
	static int[] matching;
	static int[] layer;
	
	public static List<Integer> getLayers(int sizeLeft, int sizeRight) {
		List<Integer> openRight = new LinkedList<>(); 
		Queue<Integer> q = new LinkedList<>();
		Arrays.fill(layer, -1);
		for(int i=0;i<sizeLeft;i++) {
			if (matching[i] == -1) {
				q.add(i);
				layer[i] = 0;
			}
		}
		
		while(!q.isEmpty()) {
			int current = q.poll();
			if (current >= sizeLeft && matching[current] == -1) openRight.add(current);
			
			for (int next : adj[current]) {
				if (layer[next] == -1) {
					
					// From right we want matched edges
					if(current >= sizeLeft) {
						if(matching[current] != -1 && matching[current] == next) {
							q.add(next);
							layer[next] = layer[current] +1;
						}
					}
					
					// From left we want unmatched edges
					if(current < sizeLeft && (matching[current] == -1 || matching[current] != next)) {
						q.add(next);
						layer[next] = layer[current] +1;
					}
				}
			}
		}
		return openRight;
	}
	
	static Stack<Integer> path;
	public static boolean getPath(int sizeLeft, int sizeRight, int current, boolean[] seen) {
		if(seen[current]) return false;
		path.push(current);
		seen[current] = true;
		if(current < sizeLeft && matching[current] == -1) return true;
		for( int next : adj[current]) {
			if(layer[next]+1  == layer[current]) {
				// Left side => backtrack along matched edge
				if (current < sizeLeft && matching[current] == next) {
					if (getPath(sizeLeft, sizeRight, next, seen)) return true;
				}
				// Right side => backtrack along unmatched edge
				if (current >= sizeLeft && (matching[current] == -1 || matching[current] != next)) {
					if (getPath(sizeLeft, sizeRight, next, seen)) return true;
				}
				
			}
		}
		path.pop();
		
		return false;
	}
	
	public static boolean augmentPaths(int sizeLeft, int sizeRight, List<Integer> openRight) {
		boolean pathFound = false;
		
		boolean[] seen = new boolean[sizeLeft+sizeRight]; 
		for(int right : openRight) {
			path = new Stack<>();
			if(getPath(sizeLeft, sizeRight, right, seen)) {
				pathFound = true;
				// Augment the path
				int left = -1;
				//System.out.print("Path: ");
				while(!path.isEmpty()) {
					int current = path.pop();
					//System.out.print(current + " ");
					if (current >= sizeLeft) {
						matching[current] = left;
						matching[left] = current;
					} else {
						left = current;
					}
				}
				//System.out.println(" ");
			}
		}
		
		return pathFound;
	}
	
	
	public static int hopcroftKarp(int sizeLeft, int sizeRight) {
		
		List<Integer> openRight;
		do {
			openRight = getLayers(sizeLeft, sizeRight);
		} while(augmentPaths(sizeLeft, sizeRight, openRight));
		
		int matchingSize = 0;
		for(int i=0;i<sizeLeft;i++) {
			if(matching[i] != -1) matchingSize++;
		}
			
		return matchingSize;
	}
	
	public static void main(String[] args) throws IOException {
		
		Reader.init();
		int m = Reader.nextInt();
		int n = Reader.nextInt();
		int k = Reader.nextInt();
		
		adj = new ArrayList[n+m+2];
		for(int i=0;i<n+m+2;i++) {
			adj[i] = new ArrayList<>();
		}
		
		for(int i=0;i<k;i++) {
			int from = Reader.nextInt()-1;
			int to = Reader.nextInt()-1;
			
			adj[from].add(m+2+to);
			adj[m+2+to].add(from);
		}
		
		matching = new int[n+m+2];
		layer = new int[n+m+2];
		Arrays.fill(matching, -1);
		
		int matchingSize = hopcroftKarp(m+2,n);
		
		int[] matchingBak = Arrays.copyOf(matching, matching.length);
		
		for(int i=0;i<m;i++) {
			
			if(matching[i] != -1) {
				
				// If we used the socket copy it
				adj[m] = adj[i];
				adj[m+1] = adj[i];
				for(int j: adj[i]) {
					adj[j].add(m);
					adj[j].add(m+1);
				}
			
				matchingSize = Math.max(matchingSize, hopcroftKarp(m+2, n));
				for(int j: adj[i]) {
					adj[j].remove(adj[j].size()-1);
					adj[j].remove(adj[j].size()-1);
				}
				
				// Recover matching
				for( int l = 0; l<n+m+2;l++) 
					matching[l] = matchingBak[l];
				
			}
		}
		
		System.out.println(matchingSize);
	}
	
	static class Reader {
	    static BufferedReader reader;
	    static StringTokenizer tokenizer;

	    static void init() {
	        reader = new BufferedReader(
	                     new InputStreamReader(System.in) );
	        tokenizer = new StringTokenizer("");
	    }

	    static String next() throws IOException {
	        while ( ! tokenizer.hasMoreTokens() ) {
	            tokenizer = new StringTokenizer(
	                   reader.readLine() );
	        }
	        return tokenizer.nextToken();
	    }

	    static int nextInt() throws IOException {
	        return Integer.parseInt( next() );
	    }
	}
	
}
