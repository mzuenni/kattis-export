import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.StringTokenizer;

public class PlugitinMoritz {

	static int m, n;
	static List<Integer>[] graph;
	static boolean seen[];
	static int[] matchL;
	static int[] matchR;

    static int partialMaximumMatching(int from, int to) {
        int res = 0;
        for (int i = from; i <= to; i++) {
            Arrays.fill(seen, false);
            if (isMatchable(i)) res++;
        }
        return res;
    }

    static boolean isMatchable(int u) {
        //try to match with all vertices on right side
        for (int v : graph[u]) {
            if (seen[v]) continue;
            seen[v] = true;
            //match u and v, if v is unassigned, or if v's match on the left side can be reassigned to another right vertex
            if (matchR[v] == -1 || isMatchable(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        return false;
    }

  public static void main(String[] args) throws IOException {
	  
	Reader reader = new Reader();
        reader.init();
        	
	m = reader.nextInt();
	n = reader.nextInt();
	int k = reader.nextInt();
	
	graph = new List[m+2];
	for(int i=0; i<m+2;i++) {
		graph[i] = new LinkedList<>();
	}
	
	for(int i=0;i<k;i++) {
		int from = reader.nextInt()-1;
		int to = reader.nextInt()-1;	
		graph[from].add(to);
	}
	matchL = new int[m+2];
	matchR = new int[n];
	seen = new boolean[n];
	
	// Backups of  matching structure 
	int[] recMatchL;
	int[] recMatchR;
	
	Arrays.fill(matchL, -1);
    Arrays.fill(matchR, -1);
	
	int mm = partialMaximumMatching(0,m-1);
	
	// Save backup
	recMatchL = Arrays.copyOf(matchL, matchL.length);
	recMatchR = Arrays.copyOf(matchR, matchR.length);
	
	int res = 0;
	for(int i=0;i<m;i++) {
		// If the socket was used in the original matching, it might make sense to triple it.
		if (recMatchL[i] != -1) {
			graph[m] = graph[i];
			graph[m+1] = graph[i];
			
			res = Math.max(res, mm + partialMaximumMatching(m,m+1));
			
			// Restore backup
			matchL = Arrays.copyOf(recMatchL, recMatchL.length);
			matchR = Arrays.copyOf(recMatchR, recMatchR.length);
		}
	}
	System.out.println(res);
	
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


