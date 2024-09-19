import java.util.*;
import java.io.*;

public class PaulCustomDeque {
	BufferedReader br;
	StringTokenizer st;

	int readInt() throws Exception {
		while (!st.hasMoreTokens()) {
			st = new StringTokenizer(br.readLine());
		}
		return Integer.valueOf(st.nextToken());
	}
	
	class Point {
		int x, y;
		
		public Point(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}

	long turn(Point a, Point b, Point c) {
		return (long)(b.x-a.x)*(c.y-a.y) - (long)(c.x-a.x)*(b.y-a.y);
	}

	class PointDeque {
		Point[] points;
		int head, tail, sign;

		public PointDeque(int size, int sign) {
			this.points = new Point[size];
			this.head = 0;
			this.tail = 0;
			this.sign = sign;
		}

		int size() {
			return tail-head;
		}

		Point get(int index) {
			return points[head+index];
		}

		void add(Point p) {
			points[tail++] = p;
			while (tail-head >= 3 && sign * turn(points[tail-3], points[tail-2], points[tail-1]) >= 0) {
				points[tail-2] = points[tail-1];
				tail--;
			}
		}
	}

	PointDeque lower, upper;
	List<Point> answer;

	void addGate(int x, int yMin, int yMax) {
		lower.add(new Point(x, yMin));
		upper.add(new Point(x, yMax));

		while (turn(lower.get(0), lower.get(1), upper.get(1)) <= 0) {
			answer.add(lower.get(0));
			if (lower.size() >= 3) {
				upper.points[upper.head] = lower.points[++lower.head];
			} else if (upper.size() >= 3) {
				lower.points[lower.head] = upper.points[++upper.head];
			} else {
				break;
			}
		}
	}

	void run() throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		
		Point a = new Point(readInt(), readInt());
		Point b = new Point(readInt(), readInt());
		
		int n = readInt();
		
		lower = new PointDeque(n+2, 1);
		upper = new PointDeque(n+2, -1);
		answer = new ArrayList<>();
		
		lower.add(a);
		upper.add(a);

		while (n --> 0) {
			addGate(readInt(), readInt(), readInt());
		}
		
		addGate(b.x, b.y, b.y);

		answer.add(b);
	
		PrintWriter out = new PrintWriter(System.out);
		for (Point p: answer) {
			out.println(p.x + " " + p.y);
		}
		out.close();
	}

	public static void main(String[] args) throws Exception {
		new PaulCustomDeque().run();
	}
}
