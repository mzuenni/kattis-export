import java.util.Scanner;
import java.util.Locale;
import java.math.*;

/**
 * @author Stefan Toman (toman@tum.de)
 */
public class CakeStefanBinary_tobibigdec {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		sc.useLocale(Locale.US);

		// read input
		double a = sc.nextDouble();
		int n = sc.nextInt();

		Point[] vertices = new Point[n];
		for (int j = 0; j < n; j++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			vertices[j] = new Point(x, y);
		}
		
		double min = 2;
		double max = Double.MAX_VALUE/10e6;
		
		while(max-min > 10e-6) {
			double mid = (max+min)/2;
			double aTmp = cutAreaRatio(vertices, mid);
			if(aTmp < 1-a) {
				max = mid;
			}
			else {
				min = mid;
			}
		}

		// output
		System.out.println((max+min)/2);

		sc.close();
	}

	public static double area(Point a, Point b, Point c) {
		MathContext mc = new MathContext(500);
		System.err.println("a.x = " + a.x + ", b.y = " + b.y);
		BigDecimal bd = new BigDecimal(a.x, mc).multiply(new BigDecimal(b.y, mc));
		bd = bd.add(new BigDecimal(a.y, mc).multiply(new BigDecimal(c.x, mc)));
		bd = bd.add(new BigDecimal(b.x, mc).multiply(new BigDecimal(c.y, mc)));
		bd = bd.subtract(new BigDecimal(a.x, mc).multiply(new BigDecimal(c.y, mc)));
		bd = bd.subtract(new BigDecimal(a.y, mc).multiply(new BigDecimal(b.x, mc)));
		bd = bd.subtract(new BigDecimal(b.y, mc).multiply(new BigDecimal(c.x, mc)));
		bd = bd.abs();
		bd = bd.divide(new BigDecimal("2", mc));
		return bd.doubleValue();
	}

	public static Point between(Point a, Point b, double ratio) {
		return new Point(((ratio - 1) * a.x + b.x) / ratio,
				((ratio - 1) * a.y + b.y) / ratio);
	}

	static class Point {
		double x, y;

		public Point(double x, double y) {
			super();
			this.x = x;
			this.y = y;
		}
	}

	public static double vertexArea(Point[] vertices, double s) {
		double vertexArea = 0;
		for (int j = 1; j <= vertices.length; j++) {
			vertexArea += area(
					between(vertices[j % vertices.length], vertices[j - 1], s),
					between(vertices[j % vertices.length], vertices[(j + 1)
							% vertices.length], s), vertices[j
							% vertices.length]);
		}
		return vertexArea;
	}
	
	public static double cutAreaRatio(Point[] vertices, double s) {
		double area = 0;
		for (int j = 1; j < vertices.length - 1; j++) {
			area += area(vertices[0], vertices[j], vertices[j + 1]);
		}
		
		return vertexArea(vertices, s)/area;
	}
}
