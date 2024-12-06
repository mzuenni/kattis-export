import java.util.*;
import java.util.stream.*;

public class Paul {
    static class Point {
        int x, y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj == null) return false;
            if (obj.getClass() != this.getClass()) return false;
            final Point p = (Point) obj;
            return x == p.x && y == p.y;
        }

        @Override
        public int hashCode() {
            return x * 1001 + y;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Set<Point> points = new HashSet<Point>();
        for (int i = 0; i < 5; i++) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            points.add(new Point(x, y));
        }

        int res = 0;
        for (int z = 0; z < 20; z++) {
            if (points.size() == 1) break;
            int[] xs = points.stream().mapToInt(p -> p.x).sorted().toArray();

            for (Point p: points) {
                res += Math.max(xs[1] - p.x, 0);
            }

            points = points.stream()
                .map(p -> new Point(-p.y, Math.max(p.x, xs[1])))
                .collect(Collectors.toSet());
        }

        int n = points.size();
        int[] xs = points.stream().mapToInt(p -> p.x).sorted().toArray();
        int[] ys = points.stream().mapToInt(p -> p.y).sorted().toArray();
        int dx = xs[n-1] - xs[0];
        int dy = ys[n-1] - ys[0];
        res += 2*dx + 2*dy;
        for (Point p: points) {
            if (p.x != xs[0] && p.x != xs[n-1] && p.y != ys[0] && p.y != ys[n-1]) {
                res += Math.min(dx, dy);
            }
        }
        System.out.println(res);
    }
}
