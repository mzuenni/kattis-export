import java.util.*;

public class jannik {
  static class IntList extends ArrayList<Integer> {}
  static IntList g[];
  static int vis[];
  static void dfs(int i, int v) {
    if ((vis[i] & v) != 0)
      return;
    vis[i] |= v;
    for (int j : g[i])
      dfs(j, v);
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), m = in.nextInt();
    g = new IntList[n];
    for (int i = 0; i < n; i++)
      g[i] = new IntList();
    while (m-- > 0) {
      int a = in.nextInt() - 1;
      g[a].add(in.nextInt() - 1);
    }
    vis = new int[n];
    dfs(in.nextInt() - 1, 1);
    dfs(in.nextInt() - 1, 2);
    for (int i = 0; i < n; i++)
      if (vis[i] == 3) {
        System.out.println("yes\n" + (i + 1));
        return;
      }
    System.out.println("no");
  }
}
