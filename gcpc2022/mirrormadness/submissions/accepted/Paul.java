import java.io.*;
import java.util.*;

public class Paul {
	static class IntSet extends TreeSet<Integer> { }
	static class IntMap extends TreeMap<Integer,Character> { }

	public static void main(String[] args) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String[] nums = br.readLine().split(" ");
		int n = Integer.valueOf(nums[0]);
		int m = Integer.valueOf(nums[1]);

		int[] px = new int[n];
		int[] py = new int[n];

		int xmin = Integer.MAX_VALUE;
		int xmax = Integer.MIN_VALUE;
		int ymin = Integer.MAX_VALUE;
		int ymax = Integer.MIN_VALUE;
		for (int i = 0; i < n; i++) {
			nums = br.readLine().split(" ");
			int u = Integer.valueOf(nums[0]);
			int v = Integer.valueOf(nums[1]);
			px[i] = u+v;
			py[i] = u-v;
			xmin = Math.min(xmin, px[i]);
			xmax = Math.max(xmax, px[i]);
			ymin = Math.min(ymin, py[i]);
			ymax = Math.max(ymax, py[i]);
		}

		IntSet[] x2y = new IntSet[(xmax-xmin)/2];
		IntSet[] y2x = new IntSet[(ymax-ymin)/2];
		IntMap[] mir = new IntMap[(xmax-xmin)/2];
		Arrays.setAll(x2y, x -> new IntSet());
		Arrays.setAll(y2x, x -> new IntSet());
		Arrays.setAll(mir, x -> new IntMap());

		for (int i = 0; i < n; i++) {
			int j = (i+1) % n;
			int dx = Integer.signum(px[j]-px[i]);
			int dy = Integer.signum(py[j]-py[i]);
			for (int k = 0; k < Math.abs(px[j]-px[i])/2; k++) {
				int x = (px[i]+(2*k+1)*dx-xmin)/2;
				int y = (py[i]+(2*k+1)*dy-ymin)/2;
				x2y[x].add(y);
				y2x[y].add(x);
				mir[x].put(y, dx == dy ? '/' : '\\');
			}
		}

		nums = br.readLine().split(" ");
		int u = Integer.valueOf(nums[0]);
		int v = Integer.valueOf(nums[1]);
		int x = (u+v-xmin)/2;
		int y = (u-v-ymin)/2;
		int dir = 0;

		PrintWriter pw = new PrintWriter(System.out);
		while (m --> 0) {
			int nx = x;
			int ny = y;
			if (dir == 0) nx = y2x[y].higher(x);
			if (dir == 1) ny = x2y[x].higher(y);
			if (dir == 2) nx = y2x[y].lower(x);
			if (dir == 3) ny = x2y[x].lower(y);
			x = nx;
			y = ny;
			char c = mir[x].get(y);
			dir = c == '/' ? (dir^1) : (3-dir);
			
			int xx = xmin+2*x+1, yy = ymin+2*y+1;
			pw.println((xx+yy)/2 + " " + (xx-yy)/2);
		}
		pw.close();
	}
}
