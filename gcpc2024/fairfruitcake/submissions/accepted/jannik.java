import java.util.*;

public class jannik {
  static class IntList extends ArrayList<Integer> {}
  static long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a%b);
  }
  static String frac(long n, long d) {
    if (d == 1)
      return "" + n;
    long g = gcd(n, d);
    return "" + (n / g) + "/" + (d / g);
  }
  static long cross(long ax, long ay, long bx, long by) {
    return ax * by - ay * bx;
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    long[] origx = new long[n];
    long[] origy = new long[n];
    for (int i = 0; i < n; i++) {
      origx[i] = in.nextLong() * 2;
      origy[i] = in.nextLong() * 2;
    }
    final long cx = (origx[0] + origx[n/2]) / 2, cy = (origy[0] + origy[n/2]) / 2;

    long[] x, y;
    { // collapse line segments that are colinear with the centroid
      ArrayList<Long> nx = new ArrayList<>(), ny = new ArrayList<>();
      for (int k = 0, i = 0; k < n; k++, i++) {
        nx.add(origx[i]);
        ny.add(origy[i]);

        int j = i + 1 < n ? i + 1 : 0;
        if (cross(origx[i] - cx, origy[i] - cy, origx[j] - cx, origy[j] - cy) == 0) {
          i++;
          k++;
        }
      }
      if (cross(nx.get(nx.size()-1) - cx, ny.get(ny.size()-1) - cy, nx.get(0) - cx, ny.get(0) - cy) == 0) {
        nx.remove(nx.size()-1);
        ny.remove(ny.size()-1);
      }
      n = nx.size();
      x = nx.stream().mapToLong(i -> i).toArray();
      y = ny.stream().mapToLong(i -> i).toArray();
  	}

    Integer[] order = new Integer[n];
    for (int i = 0; i < n; i++) order[i] = i;
    Arrays.sort(order, (i,j) -> {
      long llx = x[i] - cx, lly = y[i] - cy;
      long rrx = x[j] - cx, rry = y[j] - cy;
  		boolean bl = llx < 0 || (llx == 0 && lly < 0);
  		boolean br = rrx < 0 || (rrx == 0 && rry < 0);
  		if (bl) { llx = -llx; lly = -lly; }
  		if (br) { rrx = -rrx; rry = -rry; }
  		long c = cross(llx, lly, rrx, rry);
  		return c < 0 ? 1 : c > 0 ? -1 : 0;
    });

    boolean[] concave = new boolean[n];
    int[] type = new int[n];
    for (int i = 0, j = 1, k = 2, l = 0; l < n; i = j, j = k, k = (k + 1 < n ?  k+1 : 0), l++) {
      concave[j] = cross(x[j] - x[i], y[j] - y[i], x[k] - x[i], y[k] - y[i]) < 0;
      if (cross(x[i] - cx, y[i] - cy, x[j] - cx, y[j] - cy) > 0) type[i] |= 1;
      else type[j] |= 2;
    }

    boolean[] cur_open = new boolean[n];
    int num_open = 0;
    long last_x = 0, last_y = 0;
    for (int r = 0, ii = 0; r < 3 * n; ) {
      final int i = order[ii];
      if (r >= 2 * n && num_open == 2) {
        if ((last_x - cx) * (x[i] - cx) + (last_y - cy) * (y[i] - cy) < 0) {
          last_x = cx - (last_x - cx);
          last_y = cy - (last_y - cy);
        }
        System.out.println(frac(cx, 2) + " " + frac(cy, 2) + " " + frac(last_x + x[i], 4) + " " + frac(last_y + y[i], 4));
        return;
      }
      boolean impossible = false;
      IntList[] pts = new IntList[]{new IntList(), new IntList(), new IntList(), new IntList()};
      for (; cross(x[i] - cx, y[i] - cy, x[order[ii]] - cx, y[order[ii]] - cy) == 0; ii = (ii + 1 < n ? ii + 1 : 0), r++) {
        pts[type[order[ii]]].add(order[ii]);
        if ((type[order[ii]] == 3 || type[order[ii]] == 0) && concave[order[ii]])
          impossible = true;
        last_x = x[order[ii]];
        last_y = y[order[ii]];
      }

      for (int t = 0; t < 4; t++) {
        for (Integer j : pts[t]) {
          final int pre = (j == 0 ? n : j) - 1;

          if ((t & 2) != 0) { // open
            num_open++;
            cur_open[pre] = true;
          } else if (cur_open[pre]){ // close
            num_open--;
            cur_open[pre] = false;
          }

          if ((t & 1) != 0) { // open
            num_open++;
            cur_open[j] = true;
          } else if (cur_open[j]) { // close
            num_open--;
            cur_open[j] = false;
          }
        }
        if (!impossible && t == 2 && r >= n && num_open == 2) {
          System.out.println(frac(cx, 2) + " " + frac(cy, 2) + " " + frac(x[i], 2) + " " + frac(y[i], 2));
          return;
        }
      }
    }
    System.out.println("impossible");
  }
}
