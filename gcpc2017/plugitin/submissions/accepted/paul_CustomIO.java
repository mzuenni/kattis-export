import java.io.*;
import java.util.*;

class solution {
	int m, n, k;
	List<Integer>[] adj;
	int[] pred;
	boolean[] mark;

	boolean find_match(int i) {
		if (i == -1) return true;
		for (int j: adj[i]) {
			if (mark[j]) continue;
			mark[j] = true;
			if (find_match(pred[j])) {
				pred[j] = i;
				return true;
			}
		}
		return false;
	}

	int max_matching(int from, int to) {
		int res = 0;
		for (int i = from; i < to; i++) {
			Arrays.fill(mark, false);
			if (find_match(i)) res++;
		}
		return res;
	}
	
	int readInt(BufferedReader br) throws IOException {
		char c = (char) br.read();
		while (Character.isWhitespace(c)) c = (char) br.read();
		int res = 0;
		while (!Character.isWhitespace(c)) {
			res = 10*res + c-'0';
			c = (char) br.read();
		}
		return res;
	}

	void run() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		m = readInt(br);
		n = readInt(br);
		k = readInt(br);

		adj = new ArrayList[m+2];
		for (int i = 0; i < m; i++) adj[i] = new ArrayList<>();
		pred = new int[n];
		Arrays.fill(pred,-1);
		mark = new boolean[n];
		
		for (int i = 0; i < k; i++) {
			int a = readInt(br) - 1;
			int b = readInt(br) - 1;
			adj[a].add(b);
		}
		
		int match_base = max_matching(0,m), match_extra = 0;
		int[] old_pred = pred.clone();

		for (int i = 0; i < m; i++) {
			System.arraycopy(old_pred,0,pred,0,n);
			adj[m] = adj[m+1] = adj[i];
			match_extra = Math.max(match_extra, max_matching(m,m+2));
		}
		System.out.println(match_base + match_extra);
	}
}

public class paul_CustomIO {
	public static void main(String[] args) throws IOException {
		solution s = new solution();
		s.run();
	}
}
