import java.util.*;
import java.io.*;

public class PaulDeque {
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

	Deque<Point> lower, upper;
	List<Point> answer;

	void addGate(int x, int yMin, int yMax) {
		{
			Point bot = new Point(x, yMin);
			Point last = lower.pollLast();
			while (!lower.isEmpty() && turn(lower.getLast(), last, bot) >= 0) {
				last = lower.pollLast();
			}
			lower.addLast(last); lower.addLast(bot);
		}
		{
			Point top = new Point(x, yMax);
			Point last = upper.pollLast();
			while (!upper.isEmpty() && turn(upper.getLast(), last, top) <= 0) {
				last = upper.pollLast();
			}
			upper.addLast(last); upper.addLast(top);
		}
		{
			Point root = lower.pollFirst();
			upper.removeFirst();
			while (turn(root, lower.getFirst(), upper.getFirst()) <= 0) {
				answer.add(root);
				if (lower.size() >= 2) {
					root = lower.pollFirst();
				} else if (upper.size() >= 2) {
					root = upper.pollFirst();
				} else break;
			}
			lower.addFirst(root);
			upper.addFirst(root);
		}
	}

	void run() throws Exception {
		br = new BufferedReader(new InputStreamReader(System.in));
		st = new StringTokenizer(br.readLine());
		
		Point a = new Point(readInt(), readInt());
		Point b = new Point(readInt(), readInt());
		
		int n = readInt();
		
		lower = new ArrayDeque<>();
		upper = new ArrayDeque<>();
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
		new PaulDeque().run();
	}
}
