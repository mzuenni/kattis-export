import java.util.*;

class Point implements Comparable<Point> {
	int x, y, c;

	public Point(int x, int y, int c) {
		this.x = x;
		this.y = y;
		this.c = c;
	}

	public void reflect() {
		x = -x;
		y = -y;
	}

	public int compareTo(Point p) {
		if (this.x != p.x) return Integer.compare(this.x, p.x);
		return 0; //Integer.compare(this.y, p.y);
	}
}

public class paul_combs_unsorted_y {	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		
		List<Point> points = new ArrayList<Point>();
		for (int i = 0; i < n; i++) {
			int x = sc.nextInt();
			int y = sc.nextInt();
			x *= 10;
			y *= 10;
			int c = sc.nextInt();
			points.add(new Point(x, y, c));
		}
		
		Point min = new Point(Integer.MAX_VALUE, Integer.MAX_VALUE, 0);
		Point max = new Point(Integer.MIN_VALUE, Integer.MIN_VALUE, 0);
		for (Point p: points) {
			min.x = Math.min(min.x, p.x);
			min.y = Math.min(min.y, p.y);
			max.x = Math.max(max.x, p.x);
			max.y = Math.max(max.y, p.y);
		}
		Collections.sort(points);
		
		for (int k = 0; k < 2; k++) {
			List<Point> poly = new ArrayList<Point>();
			int i = 0;
			while (i < n) {
				int x = points.get(i).x;
				
				poly.add(new Point(x+2, min.y-3, 0));
				
				for (; i < n; i++) {
					Point p = points.get(i);
					if (p.x != x) break;
					if (p.c != k+1) continue;
					poly.add(new Point(x+2, p.y-1, 0));
					poly.add(new Point(x-1, p.y-1, 0));
					poly.add(new Point(x-1, p.y+1, 0));
					poly.add(new Point(x+2, p.y+1, 0));
				}				
				
				poly.add(new Point(x+2, max.y+2, 0));
				poly.add(new Point(x+4, max.y+2, 0));
				poly.add(new Point(x+4, min.y-3, 0));
			}
			poly.add(new Point(max.x+4, min.y-5, 0));
			poly.add(new Point(min.x+2, min.y-5, 0));

			System.out.println(poly.size());
			for (Point p : poly) {
				if (k == 1) p.reflect();
				System.out.format("%.1f %.1f\n", 0.1 * p.x, 0.1 * p.y);
			}
			min.reflect();
			max.reflect();
			Point tmp = min;
			min = max;
			max = tmp;
			for (Point p: points) p.reflect();
			Collections.reverse(points);
		}
	}
	


}
