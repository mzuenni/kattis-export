import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.math.*;

/*
Solution explanation:
If you accelerate for x seconds, then you travel 0.5 * x^2 metres,
and the speed is then x m/s. If we spend fuel on a segment, it is
optimal to spend half of the fuel accelating in the beginning,
then travelling at the same speed, and then decellerating for
the same time. So, if we call t(f,d) the time it takes to traverse
a segment of length d with f fuel, this is:
t(f,d) = f + (d - (f/2)^2) / (f / 2) = f / 2 + 2 d / f

We know that in the optimal solution, increasing f will make
t lower. If we have two segments, it should there hold that the slope
of the two segments at the optimal fuel distribution is the same,
because otherwise we could remove a bit of fuel from one segment
and add it to the other one to get a lower total time.

Formally, the partial derivative in f should be the same for the two
segments, so:
∂ t(f1,d1) / ∂ f1 = ∂ t(f2,d2) / ∂ f2
∂ t(f,d) / ∂ f = 1/2 - 2d / f^2

Let's call this number X, which should be the same for all segments,
so for any segment d_i with fuel consumption f_i we have:
X = 1/2 - 2d_i / f_i^2
1/2 - X = 2d_i / f_^2
f_i^2 = 2d_i / (1/2 - X)
f_i = sqrt(2d_i / (1/2 - X))

For the optimal solution we should spend all given time, so we know
that sum_i t(f_i,d_i) = t must hold. Filling in f_i from the above
gives:

sum_i t(f_i,d_i)
  = sum_i( sqrt(2d_i / (1/2 - X)) / 2 + 2 d_i / sqrt(2d_i / (1/2 - X)) )
  = sum_i( sqrt(2d_i) / 2 sqrt(1/2 - X) + 2 d_i * sqrt(1/2 - X) / sqrt(2d_i) )
  = 1 / 2 sqrt(1/2 - X) * sum_i(sqrt(2d_i)) + sqrt(1/2 - X) * sum_i(sqrt(2d_i) )
  = (1 / 2 sqrt(1/2 - X) + sqrt(1/2 - X)) * sum_i(sqrt(2d_i))
  = t

Now we have isolated the sum, so we can expres X in terms of t and 
sum_i(sqrt(2d_i)) = Y (introducing a name for this constant term):
t = (1 / 2 sqrt(1/2 - X) + sqrt(1/2 - X)) * Y
t / Y = 1 / 2 sqrt(1/2 - X) + sqrt(1/2 - X)
sqrt(1/2 - X) * t / Y = 1/2 + 1/2 - X = 1 - X
(1/2 - X) * t^2 / Y^2 = (1 - X)^2 = X^2 - 2 X + 1
1/2 t^2 / Y^2 - X * (t^2 / Y^2)  = X^2 - 2 X + 1
0 = X^2 + ((t^2 / Y^2) - 2) X + (1 - 1/2 t^2 / Y^2)

This can be solved using the standard technique for solving quadratic equations:
a = 1
b = t^2 / Y^2 - 2
c = 1 - 1/2 t^2 / Y^2
d = b^2 - 4 a c
    = (t^2 / Y^2 - 2)^2 - 4 * (1 - 1/2 t^2 / Y^2)
    = 4 - 4 * t^2 / Y^2 + t^4 / Y^4 - 4 + 2 * t^2 / Y^2
    = 2 * t^2 / Y^2 - 4 * t^2 / Y^2 + t^4 / Y^4
    = (t^4 / Y^2 - 2 * t^2) / Y^2

This means we have a solution when
(t^4 / Y^2 - 2 * t^2) / Y^2 >= 0
t^4 / Y^2 - 2 * t^2 >= 0
t^4 / Y^2 >= 2 * t^2
t^2 / Y^2 >= 2
t^2 >= 2 * Y^2

Then we the solution is:
X = (-sqrt(d) - b) / 2a
  = (-sqrt((t^4 / Y^2 - 2 * t^2) / Y^2) - t^2 / Y^2 + 2) / 2
  = 1 - sqrt(t^4 / Y^2 - 2 * t^2) / 2 Y - t^2 / 2 Y^2

Filling in X to find the amount of fuel:
f_i = sqrt(2d_i / (1/2 - X))
    = sqrt(2d_i / (sqrt(t^4 / Y^2 - 2 * t^2) / 2 Y + t^2 / 2 Y^2 - 1/2))
    = sqrt(2d_i) / sqrt(sqrt(t^4 / Y^2 - 2 * t^2) / 2 Y + t^2 / 2 Y^2 - 1/2)

The answer to our problem is then:
ans = sum_i(f_i)
    = sum_(sqrt(2d_i)) / sqrt(sqrt(t^4 / Y^2 - 2 * t^2) / 2 Y + t^2 / 2 Y^2 - 1/2)
    = Y / sqrt(sqrt(t^4 / Y^2 - 2 * t^2) / 2 Y + t^2 / 2 Y^2 - 1/2)
 */


public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

	public static void main(String[] args) throws Exception {
		// Read input
		String[] ps = in.readLine().split(" ");
		int n = Integer.valueOf(ps[0]);
		int m = Integer.valueOf(ps[1]);
		int q = Integer.valueOf(ps[2]);

		Point3D[] pts = new Point3D[n];
		for(int i = 0; i < n; i++)
			pts[i] = Point3D.valueOf(in.readLine());

		ArrayList<Integer>[] nbs = new ArrayList[n];
		for(int i = 0; i < n; i++) nbs[i] = new ArrayList<Integer>();

		for(int i = 0; i < m; i++) {
			ps = in.readLine().split(" ");
			int a = Integer.valueOf(ps[0]);
			int b = Integer.valueOf(ps[1]);
			nbs[a-1].add(b-1);
			nbs[b-1].add(a-1);
		}
		int[] cs = new int[q];
		int[] ts = new int[q];
		for(int i = 0; i < q; i++) {
			ps = in.readLine().split(" ");
			cs[i] = Integer.valueOf(ps[0]) - 1;
			ts[i] = Integer.valueOf(ps[1]);
		}

		// Compute sum(sqrt(2 d_i)) from planet 1 to each i using Dijkstra
		boolean[] visited = new boolean[n];
		double[] sumsqrt = new double[n];
		PriorityQueue<State> Q = new PriorityQueue<State>();
		Q.offer(new State(0, 0));
		while(!Q.isEmpty()) {
			State top = Q.poll();
			if(visited[top.i]) continue;
			visited[top.i] = true;
			sumsqrt[top.i] = top.d;
			for(int j : nbs[top.i]) {
				double dd = pts[top.i].distance(pts[j]);
				Q.offer(new State(j, top.d + Math.sqrt(2 * dd)));
			}
		}

		// Handle all queries
		for(int i = 0; i < q; i++) {
			double t = ts[i];
			double y = sumsqrt[cs[i]];
			if(t * t < 2 * y * y || !visited[cs[i]]) {
				System.out.println("impossible");
			} else {
				double ans = y / Math.sqrt(Math.sqrt(t*t*t*t / (y*y) - 2 * t * t) / (2 * y) + t * t / (2 * y * y) - 0.5);
				System.out.println(ans);
			}
		}
	}

	static class State implements Comparable<State> {
		int i;
		double d;

		public State(int i, double d) {
			this.i = i;
			this.d = d;
		}

		public int compareTo(State other) {
			return Double.compare(this.d, other.d);
		}
	}

	static class Point3D {
		public int x, y, z;

		public Point3D(int x, int y, int z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}

		public static Point3D valueOf(String s) {
			String[] ps = s.split(" ");
			return new Point3D(Integer.valueOf(ps[0]), Integer.valueOf(ps[1]), Integer.valueOf(ps[2]));
		}

		public double distance(Point3D other) {
			long sum = (long)(this.x - other.x) * (this.x - other.x)
				+ (long)(this.y - other.y) * (this.y - other.y)
				+ (long)(this.z - other.z) * (this.z - other.z);
			return Math.sqrt(sum);
		}
	}
}
