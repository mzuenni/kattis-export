import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class Tobias {
  private static final class Point {
    public final long x;
    public final long y;

    public Point(long x, long y) {
      this.x = x;
      this.y = y;
    }

    Point flipX() {
      return new Point(-x, y);
    }

    Point flipY() {
      return new Point(x, -y);
    }
  }

  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      String[] aData = reader.readLine().split(" ");
      String[] bData = reader.readLine().split(" ");
      Point a = new Point(Long.parseLong(aData[0]), Long.parseLong(aData[1]));
      Point b = new Point(Long.parseLong(bData[0]), Long.parseLong(bData[1]));
      long r = Long.parseLong(aData[2]);
      long s = Long.parseLong(bData[2]);

      long dx = Math.abs(b.x - a.x);
      long dy = Math.abs(b.y - a.y);
      long gap = dx + dy - r - s;
      if (gap > 0 || gap % 2 != 0) {
        System.out.println("impossible");
      } else {
        Point c = solve(a, r, b, s);
        System.out.printf("%d %d%n", c.x, c.y);
      }
    }
  }

  private static Point solve(Point a, long r, Point b, long s) {
    if (r > s) {
      return solve(b, s, a, s);
    }
    if (a.x > b.x) {
      return solve(a.flipX(), r, b.flipX(), s).flipX();
    }
    if (a.y > b.y) {
      return solve(a.flipY(), r, b.flipY(), s).flipY();
    }

    long dx = b.x - a.x;
    return r < dx ? new Point(a.x + r, a.y) : new Point(b.x, a.y + r - dx);
  }
}
