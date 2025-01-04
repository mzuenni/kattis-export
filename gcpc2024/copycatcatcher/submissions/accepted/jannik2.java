import java.util.*;

public class jannik2 {
  static int[] prev(int k, int[] s) {
    int[] res = new int[s.length - k];
    int[] last = new int[256];
    for (int i = 0; i < s.length - k; i++) {
      if (s[i + k] < 0)
        res[i] = s[i + k];
      else {
        if (last[s[i + k]] != 0)
          res[i] = i + 1 - last[s[i + k]];
        last[s[i + k]] = i + 1;
      }
    }
    return res;
  }

  static Scanner in = new Scanner(System.in);

  static int[] read() {
    in.nextLine(); // n
    String s = in.nextLine();
    int[] res = new int[s.length()];
    for (int i = 0; i < res.length; i++)
      if ((i == 0 || Character.isWhitespace(s.charAt(i - 1)))
          && (i + 1 == res.length || Character.isWhitespace(s.charAt(i + 1)))
          && Character.isLetter(s.charAt(i)))
        res[i] = (int) s.charAt(i);
      else
        res[i] = -(int) s.charAt(i);
    return res;
  }

  public static void main(String[] args) {
    int[] code = read();
    int n = code.length;
    int[][] prevs = new int[n][];
    for (int i = 0; i < n; i++)
      prevs[i] = prev(i, code);

    Arrays.sort(prevs, (l, r) -> {
      for (int i = 0; i < l.length && i < r.length; i++)
        if (l[i] != r[i])
          return l[i] - r[i];
      return l.length - r.length;
    });
    for (int q = Integer.parseInt(in.nextLine()); q-- > 0;) {
      int[] pre = prev(0, read());
      int p = Arrays.binarySearch(prevs, pre, (l, r) -> {
        for (int i = 0; i < l.length && i < r.length; i++)
          if (l[i] != r[i])
            return l[i] - r[i];
        return l.length - r.length;
      });
      if (p < 0)
        p = -p - 1;
      boolean res = p < n;
      for (int i = 0; res && i < pre.length; i++)
        res = (pre[i] == prevs[p][i]);
      System.out.println(res ? "yes" : "no");
    }
  }
}
