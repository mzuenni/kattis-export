import java.util.Scanner;
import java.util.Locale;

/**
 * be catious not to loss significance
 */
public class CakeStefanTweaked {
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

		// output
		System.out.println(Math.sqrt(4*cutAreaRatio(vertices, 2)/(1-a)));

		sc.close();
	}

	public static double area(Point a, Point b, Point c) {
		double dX1=b.x-a.x; double dY1=b.y-a.y; //<---- 
		double dX2=c.x-a.x; double dY2=c.y-a.y;
		return Math.abs(0.5*dX1 * dY2-0.5*dX2*dY1);
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
