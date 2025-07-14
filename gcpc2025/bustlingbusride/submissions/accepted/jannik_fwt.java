import java.util.function.*;
import java.util.*;

public class jannik_fwt {
  static class Fwt {
    int[] bi_tree;

    Fwt(int n) {
      bi_tree = new int[n];
    }

    void add(int pos, int val) {
      if (pos == 0) {
        bi_tree[0] += val;
        return;
      }
      while (pos < bi_tree.length) {
        bi_tree[pos] += val;
        pos += pos & (-pos);
      }
    }

    int rank(int pos) {
      if (pos < 0)
        return 0;
      int res = bi_tree[0];
      for (; pos != 0; pos &= pos - 1)
        res += bi_tree[pos];
      return res;
    }
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), b = in.nextInt(), r = in.nextInt(), w = in.nextInt();
    long[] ts = new long[b + 1];
    for (int i = 1; i <= b; i++)
      ts[i] = ts[i - 1] + in.nextLong();
    int[] ds = new int[n];
    for (int i = 0; i < n; i++)
      ds[i] = in.nextInt();

    Function<Long, Boolean> test = (max_t) -> {
      int k = 0;
      long t = 0;
      Fwt stops = new Fwt(b + 1), people = new Fwt(b + 1);
      for (; k < n && t < max_t; t += r) {
        int max_stop = 0, wait = 0;
        final int start = k;
        while (k < n) {
          wait += stops.rank(ds[k] - 1) + 1;
          people.add(ds[k], 1);
          if (stops.rank(ds[k]) == stops.rank(ds[k] - 1)) {
            wait += k + 1 - start - people.rank(ds[k]);
            stops.add(ds[k], 1);
          }
          max_stop = Math.max(max_stop, ds[k]);
          if (t + wait * 2l * w + ts[max_stop] > max_t)
            break;
          k++;
        }
        if (start == k)
          return false;
        for (int i = start; i <= k && i < n; i++) {
          people.add(ds[i], -1);
          if (stops.rank(ds[i]) > stops.rank(ds[i] - 1))
            stops.add(ds[i], -1);
        }
      }
      return k == n;
    };
    long hi = 1;
    while (!test.apply(hi))
      hi = 2 * hi;
    long lo = hi / 2;
    while (lo + 1 < hi) {
      long m = lo + (hi - lo) / 2;
      if (test.apply(m))
        hi = m;
      else
        lo = m;
    }
    System.out.println(hi);
  }
}
