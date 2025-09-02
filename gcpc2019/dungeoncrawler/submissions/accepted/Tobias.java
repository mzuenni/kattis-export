import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.HashSet;
import java.util.Set;

public class Tobias {
  private static final class State {
    int at = 0;
    String[] item = new String[N];

    void check(String it, int itmask) {
      if (item[at] == null) {
        item[at] = it;
      }
      if (!it.equals(item[at])) {
        at = 0;
      }
      if (adjmask[at] != itmask) {
        at = 0;
      }
    }

    void move(char c) {
      at = adj[at][c - 'A'];
    }

    void fin() {
      Set<String> items = new HashSet<>();
      for (int i = 1; i <= n; i++) {
        if (item[i] == null) {
          at = 0;
        }
        items.add(item[i]);
      }
      if (items.size() != n) {
        at = 0;
      }
    }
  }

  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      n = Integer.parseInt(reader.readLine());

      for (int i = 1; i <= n; i++) {
        String[] data = reader.readLine().split(" ");
        int k = Integer.parseInt(data[0]);
        for (int j = 1; j <= k; j++) {
          char c = data[2 * j - 1].charAt(0);
          int m = Integer.parseInt(data[2 * j]);
          adj[i][c - 'A'] = m;
          adjmask[i] |= 1 << (c - 'A');
        }
      }

      for (int i = 1; i <= n; i++) {
        st[i] = new State();
        st[i].at = i;
      }

      synchronized (System.out) { // Obtain the exclusive lock for the whole interactive process
        dfs(reader);
      }

      for (int i = 1; i <= n; i++) {
        st[i].fin();
      }

      int res = 0;

      for (int i = 1; i <= n; i++) {
        if (st[i].at == 0) {
          continue;
        }
        if (res != 0) {
          System.out.println("R ambiguous");
          System.out.flush();
          return;
        }
        res = i;
      }

      if (res != 0) {
        System.out.println("R " + res);
        System.out.flush();
      } else {
        System.out.println("R no");
        System.out.flush();
      }
    }
  }

  private static void dfs(BufferedReader reader) throws IOException {
    String[] data = reader.readLine().split(" ");
    String it = data[0];
    String dirs = data[1];

    int itmask = 0;
    for (int i = 0; i < dirs.length(); i++) {
      itmask |= 1 << (dirs.charAt(i) - 'A');
    }

    for (int i = 1; i <= n; i++) {
      st[i].check(it, itmask);
    }

    boolean anyOk = false;
    for (int i = 1; i <= n; i++) {
      anyOk = anyOk || st[i].at != 0;
    }
    if (!anyOk) {
      System.out.println("R no");
      System.out.flush();
      System.exit(0);
    }

    if (!visited.add(it)) {
      return;
    }

    for (int i = 0; i < dirs.length(); i++) {
      char c = dirs.charAt(i);
      System.out.print("W ");
      System.out.println(c);
      System.out.flush();
      for (int j = 1; j <= n; j++) {
        st[j].move(c);
      }
      dfs(reader);
      System.out.print("W ");
      System.out.println(c);
      System.out.flush();
      for (int j = 1; j <= n; j++) {
        st[j].move(c);
      }
      reader.readLine();
    }
  }

  private static final int N = 1010;
  private static final int[][] adj = new int[N][26];
  private static final int[] adjmask = new int[N];
  private static final State[] st = new State[N];
  private static final Set<String> visited = new HashSet<>();
  private static int n;
}
