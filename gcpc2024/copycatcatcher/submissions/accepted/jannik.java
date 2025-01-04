import java.util.*;

public class jannik {
  static int[] prev(int k, int[] s) {
    int[] res = new int[s.length - k];
    int[] last = new int[52];
    for (int i = 0; i < s.length - k; i++) {
      if (s[i + k] < 52) {
        if (last[s[i + k]] != 0)
          res[i] = i + 1 - last[s[i + k]];
        last[s[i+k]] = i + 1;
      } else
        res[i] = s[i + k];
    }
    return res;
  }

  static HashMap<String, Integer> tokens = new HashMap<>();

  static int lookup(String s) {
    Integer tmp = tokens.putIfAbsent(s, tokens.size());
    return tmp == null ? tokens.size() - 1 : tmp;
  }

  static Scanner in = new Scanner(System.in);

  static int[] read() {
    int n = in.nextInt();
    int[] res = new int[n];
    for (int i = 0; i < n; i++)
      res[i] = lookup(in.next());
    return res;
  }

  public static void main(String[] args) {
    for (int i = 0; i < 256; i++)
      if (Character.isLetter(i))
        lookup(new String(new char[] { (char) i }));
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
    for (int q = in.nextInt(); q-- > 0;) {
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
