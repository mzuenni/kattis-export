import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;
import java.awt.geom.*;

public class jeroen {
	static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	static Point2D[] pts;

	public static void main(String[] args) throws Exception {
		// Read input
		int n = Integer.valueOf(in.readLine());
		pts = new Point2D[n];
		for(int i = 0; i < n; i++) {
			String[] ps = in.readLine().split(" ");
			pts[i] = new Point2D.Double(Integer.valueOf(ps[0]), Integer.valueOf(ps[1]));
		}

		// Try all relevant angles
		double best = Double.MAX_VALUE / 3;
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				double angle = Math.atan2(pts[i].getY() - pts[j].getY(), pts[i].getX() - pts[j].getX());
				best = Math.min(best, withAngle(angle));
			}
		}
		System.out.println(best);
	}

	static double withAngle(double angle) {
		// Precompute distances between pairs of places
		int n = pts.length;
		double[][] dist = new double[n][n];
		AffineTransform rot = AffineTransform.getRotateInstance(-angle);
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				// Construct the vector between the two points, rotate it with the angle,
				// and then the distance is dx + dy. And since everything is rotationally
				// symmetric we simply take the absolute values.
				Point2D v = new Point2D.Double(pts[i].getX() - pts[j].getX(), pts[i].getY() - pts[j].getY());
				Point2D r = rot.transform(v, null);
				dist[i][j] = dist[j][i] = Math.abs(r.getX()) + Math.abs(r.getY());
			}
		}
		
		// Dp state: places to visit, current place
		double[][] dp = new double[1<<n][n];
		for(int i = 1; i < (1<<n); i++) {
			for(int j = 0; j < n; j++) {
				dp[i][j] = Double.MAX_VALUE / 3;
				for(int k = 0; k < n; k++) {
					if((i & (1<<k)) == 0) continue;
					if(j == k) continue;
					dp[i][j] = Math.min(dp[i][j], dp[i^(1<<k)][k] + dist[j][k]);
				}
			}
		}
		double best = Double.MAX_VALUE / 3;
		for(int i = 0; i < n; i++)
			best = Math.min(best, dp[(1<<n)-(1<<i)-1][i]);
		return best;
	}
}
