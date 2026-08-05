import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class OneWayBruteForce {
	
	static final int max(int[] arr, int stopEarly) {
		int max = 0;
		for (int i : arr) {
			max = (i > max) ? i : max;
		}
		return max;
	}
	
	
	static int orient(int n, int[] u, int[] v) {
		int m = u.length;
		int[] indeg = new int[n];
		boolean[] pointsToU = new boolean[m];	// true iff this edge points to src.
		for (int i = 0; i < m; i++) {
			indeg[v[i]]++;	// this edge points to v initially
		}
		int min = Integer.MAX_VALUE;
		
		// Use Gray code generation of Bitner, Ehrlich, and Reingold (as mentioned in Knuth's TAOCP)
		int[] f = new int[m+1];	// focus pointers
		for (int j = 0; j <= m; j++) {
			f[j] = j;
		}
		int j = 0;
		while (true) {
			int thisMax = max(indeg, min);
			if (thisMax < min)
				min = thisMax;
			
			j = f[0];
			f[0] = 0;
			if (j == m)
				break;
			f[j] = f[j+1];
			f[j+1] = j+1;
			pointsToU[j] = !pointsToU[j];
//			System.out.println(Arrays.toString(pointsToU));
			if (pointsToU[j]) {
				indeg[u[j]]++;
				indeg[v[j]]--;
			}
			else {
				indeg[u[j]]--;
				indeg[v[j]]++;
			}
		}
		return min;
	}
	
	
	public static void main(final String[] args) {
		String line;
//		long start;
//		long end;
		try {
			final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			line = br.readLine();
			final int n = Integer.parseUnsignedInt(line);
			line = br.readLine();
			final int m  = Integer.parseUnsignedInt(line);
			
			int[] src = new int[m];
			int[] tar = new int[m];
			
			for (int i = 0; i < m; i++) {
				line = br.readLine();
				int blankPos = line.indexOf(' ');
				int u = Integer.parseUnsignedInt(line.substring(0, blankPos))-1;
				int v = Integer.parseUnsignedInt(line.substring(blankPos+1))-1;
//				System.out.println(u+", "+v);
//				assert(u < v);
				src[i] = u;
				tar[i] = v;
			}
			br.close();
//			start = System.currentTimeMillis();
			
			int orientationNumber = orient(n, src, tar);
			
//			end = System.currentTimeMillis();
//			System.out.println((end-start)+" ms for computing the orientation number:");
			System.out.println(orientationNumber);
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}
}
