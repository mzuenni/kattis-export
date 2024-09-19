import java.util.*;
import java.io.*;

public class PaulNoPointClass {
	BufferedReader br;
	StringTokenizer st;

	int readInt() throws Exception {
		while (!st.hasMoreTokens()) {
			st = new StringTokenizer(br.readLine());
		}
		return Integer.valueOf(st.nextToken());
	}

	long turn(int ax, int ay, int bx, int by, int cx, int cy) {
		return (long)(bx-ax)*(cy-ay) - (long)(cx-ax)*(by-ay);
	}

	int uh = 0, ut = 1, lh = 0, lt = 1, pt = 0;
	int[] ux, uy, lx, ly, px, py;

	void addGate(int x, int yMin, int yMax) {
		lx[lt] = x; ly[lt++] = yMin;
		while (lt-lh > 2 && turn(lx[lt-3], ly[lt-3], lx[lt-2], ly[lt-2], lx[lt-1], ly[lt-1]) >= 0) {
			lt--; lx[lt-1] = lx[lt]; ly[lt-1] = ly[lt];
		}
		
		ux[ut] = x; uy[ut++] = yMax;
		while (ut-uh > 2 && turn(ux[ut-3], uy[ut-3], ux[ut-2], uy[ut-2], ux[ut-1], uy[ut-1]) <= 0) {
			ut--; ux[ut-1] = ux[ut]; uy[ut-1] = uy[ut];
		}
		
		while (turn(lx[lh], ly[lh], lx[lh+1], ly[lh+1], ux[uh+1], uy[uh+1]) <= 0) {
			px[pt] = lx[lh]; py[pt++] = ly[lh];
			if (lt-lh > 2) {
				ux[uh] = lx[++lh]; uy[uh] = ly[lh];
			} else if (ut-uh > 2) {
				lx[lh] = ux[++uh]; ly[lh] = uy[uh];
			} else {
				break;
			}
		}
	}

	void run() throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		
		int ax = readInt(), ay = readInt();
		int bx = readInt(), by = readInt();
		
		int n = readInt();
		
		ux = new int[n+2];
		uy = new int[n+2];
		lx = new int[n+2];
		ly = new int[n+2];
		px = new int[n+2];
		py = new int[n+2];
		
		lx[0] = ax; ly[0] = ay;
		ux[0] = ax; uy[0] = ay;

		while (n --> 0) {
			int x = readInt(), yMin = readInt(), yMax = readInt();
			addGate(x, yMin, yMax);
		}
		
		addGate(bx, by, by);

		px[pt] = bx; py[pt++] = by;

		PrintWriter out = new PrintWriter(System.out);
		for (int i = 0; i < pt; i++) {
			out.println(px[i] + " " + py[i]);
		}
		out.close();
	}

	public static void main(String[] args) throws Exception {
		new PaulNoPointClass().run();
	}
}
