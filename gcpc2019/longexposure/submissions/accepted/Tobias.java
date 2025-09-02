import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;

public class Tobias {
  private static final class Rectangle {
    public final int xmin;
    public final int ymin;
    public final int xmax;
    public final int ymax;

    public Rectangle(int xmin, int ymin, int xmax, int ymax) {
      this.xmin = xmin;
      this.ymin = ymin;
      this.xmax = xmax;
      this.ymax = ymax;
    }
  }


  private static final class Pair {
    public final double d;
    public final int i;

    public Pair(double d, int i) {
      this.d = d;
      this.i = i;
    }
  }

  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      int n = Integer.parseInt(reader.readLine());

      List<Integer> i2x = new ArrayList<>(2 * n);
      List<Integer> j2y = new ArrayList<>(2 * n);
      i2x.add(0);
      j2y.add(0);

      Rectangle[] rects = new Rectangle[n];

      for (int i = 0; i < n; i++) {
        String[] data = reader.readLine().split(" ");
        int xmin = Integer.parseInt(data[0]);
        int ymin = Integer.parseInt(data[1]);
        int w = Integer.parseInt(data[2]);
        int h = Integer.parseInt(data[3]);
        rects[i] = new Rectangle(xmin, ymin, xmin + w, ymin + h);
        i2x.add(xmin);
        i2x.add(xmin + w);
        j2y.add(ymin);
        j2y.add(ymin + h);
      }

      Map<Integer, Integer> x2i = new HashMap<>(2 * n);
      Map<Integer, Integer> y2j = new HashMap<>(2 * n);
      compress(i2x, x2i);
      compress(j2y, y2j);

      int[][] a = new int[N][N];

      for (Rectangle rect : rects) {
        int imin = x2i.get(rect.xmin);
        int imax = x2i.get(rect.xmax);
        int jmin = y2j.get(rect.ymin);
        int jmax = y2j.get(rect.ymax);

        a[imin][jmin]++;
        a[imax][jmax]++;
        a[imin][jmax]--;
        a[imax][jmin]--;
      }

      for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
          a[i][j] += a[i + 1][j];
        }
      }
      for (int i = 0; i < N; i++) {
        for (int j = N - 2; j >= 0; j--) {
          a[i][j] += a[i][j + 1];
        }
      }
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          a[i][j] = a[i][j] == 0 ? 0 : 1;
        }
      }

      List<Pair> events = new ArrayList<>();
      for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N; j++) {
          if (a[i][j] != a[i + 1][j]) {
            int x = i2x.get(i);
            int y1 = j2y.get(j - 1);
            int y2 = j2y.get(j);

            double r1 = Math.hypot(x, y1);
            double r2 = Math.hypot(x, y2);
            if (r1 > r2) {
              double r3 = r1;
              r1 = r2;
              r2 = r3;
            }
            events.add(new Pair(r1, 1));
            events.add(new Pair(r2, -1));
          }
        }
      }
      System.out.println();

      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
          if (a[i][j] != a[i][j + 1]) {
            int x1 = i2x.get(i - 1);
            int x2 = i2x.get(i);
            int y = j2y.get(j);

            double r1 = Math.hypot(x1, y);
            double r2 = Math.hypot(x2, y);
            if (r1 > r2) {
              double r3 = r1;
              r1 = r2;
              r2 = r3;
            }
            events.add(new Pair(r1, 1));
            events.add(new Pair(r2, -1));
          }
        }
      }

      events.sort(Comparator.<Pair, Double>comparing(p -> p.d).thenComparing(p -> p.i));

      int depth = 0;
      double rprev = 0.0;
      double black = 0.0;
      double gray = 0.0;

      for (Pair event : events) {
        double rcur = event.d;
        double ring = Math.PI * (rcur * rcur - rprev * rprev);
        if (depth > 0) {
          gray += ring;
        } else {
          double r = (rprev + rcur) / 2.0;
          int i = 0;
          while (i < i2x.size() && i2x.get(i) < r) {
            i += 1;
          }
          if (a[i][y2j.get(0)] > 0) {
            black += ring;
          }
        }
        rprev = rcur;
        depth += event.i;
      }

      System.out.printf("%.20f%n%.20f%n", black, gray);
    }
  }

  private static void compress(List<Integer> i2x, Map<Integer, Integer> x2i) {
    Collection<Integer> uniqueElements = new HashSet<>(i2x.size());
    i2x.removeIf(integer -> !uniqueElements.add(integer));
    Collections.sort(i2x);

    ListIterator<Integer> listIterator = i2x.listIterator();
    while (listIterator.hasNext()) {
      int i = listIterator.nextIndex();
      x2i.put(listIterator.next(), i);
    }
  }

  private static final int N = 2010;
}
