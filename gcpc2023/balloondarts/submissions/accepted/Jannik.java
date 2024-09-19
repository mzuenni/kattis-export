import java.util.*;
//import java.util.stream.*;

public class Jannik {
	static class Pt {
		public int x;
		public int y;
		Pt (int x, int y) { this.x = x; this.y = y; }
	}

	// 1=ccw, 0=straight, -1=cw
	static int ccw(Pt p0, Pt p1, Pt p2) {
		long d1 =(p1.x-p0.x)*(p2.y-p0.y);
		long d2 =(p2.x-p0.x)*(p1.y-p0.y);
		return (d1-d2>0 ? 1 : 0) - (d2-d1>0 ? 1 : 0);
	}

	static Pt[] filter(Pt[] p, Pt a, Pt b) {
		int cnt = 0;
		for (int i = 0; i < p.length; i++)
			if (ccw(p[i], a, b) != 0)
				cnt++;
		Pt[] res = new Pt[cnt];
		cnt = 0;
		for (int i = 0; i < p.length; i++)
			if (ccw(p[i], a, b) != 0)
				res[cnt++] = p[i];
		return res;
		//return Arrays.stream(p).filter(x -> ccw(x, a, b) != 0).toArray(Pt[]::new); // this is very slow...
	}

	static boolean solve(Pt[] p, int k) {
		if (p.length <= 2*k) return true;
		for (int i = 0; i <= k; i++)
			for (int j = 0; j < i; j++)
				if (solve(filter(p, p[i], p[j]), k-1))
					return true;
		return false;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		Pt[] p = new Pt[n];
		for (int i = 0; i < n; i++)
			p[i] = new Pt(in.nextInt(), in.nextInt());
		System.out.println(solve(p, 3) ? "possible" : "impossible");
	}
}
