import java.util.*;

public class jannik {
	static class Pt {
		public long x, y;

		Pt(long a, long b) {
			x = a;
			y = b;
		}

		@Override
		public boolean equals(Object rr) {
			if (!(rr instanceof Pt))
				return false;
			Pt r = (Pt) rr;
			return x == r.x && y == r.y;
		}

		@Override
		public int hashCode() {
			return Objects.hash(x, y);
		}
	}

	static double[] avg(int[] x, int[] y) {
		double[] xy = new double[2];
		for (int i = 0; i < x.length; i++) {
			xy[0] += x[i];
			xy[1] += y[i];
		}
		xy[0] /= x.length;
		xy[1] /= x.length;
		return xy;
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] ax = new int[n];
		int[] ay = new int[n];
		for (int i = 0; i < n; i++) {
			ax[i] = in.nextInt();
			ay[i] = in.nextInt();
		}

		HashSet<Pt> b = new HashSet<>();
		int[] bx = new int[n];
		int[] by = new int[n];
		for (int i = 0; i < n; i++) {
			bx[i] = in.nextInt();
			by[i] = in.nextInt();
			Pt p = new Pt(bx[i], by[i]);
			b.add(p);
		}
		var ca = avg(ax, ay);
		var cb = avg(bx, by);
		double[] c = new double[] { (ca[0] + cb[0]) / 2, (ca[1] + cb[1]) / 2 };
		double[] normal = new double[] { ca[0] - c[0], ca[1] - c[1] };

		double normal_len2 = normal[0] * normal[0] + normal[1] * normal[1];
		for (int i = 0; i < n; i++) {
			double k = ((c[0] - ax[i]) * normal[0] + (c[1] - ay[i]) * normal[1]) / normal_len2;
			double x = ax[i] + normal[0] * 2 * k;
			double y = ay[i] + normal[1] * 2 * k;
			Pt p = new Pt(Math.round(x), Math.round(y));
			if (Math.abs(x - p.x) > 1e-5 || Math.abs(y - p.y) > 1e-5 || k >= 0 || !b.remove(p)) {
				System.out.println("impossible");
				return;
			}
		}

		System.out.println("possible");
	}
}
