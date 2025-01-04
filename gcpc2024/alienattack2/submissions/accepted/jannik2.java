import java.util.*;

public class jannik2 {
  static class IntList extends ArrayList<Integer> {}
  static IntList[] adj;
  static boolean[] vis;
  static int dfs(int i) {
    if (vis[i])
      return 0;
    vis[i] = true;
    int res = 1;
    for (int j : adj[i])
      res += dfs(j);
    return res;
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), m = in.nextInt();
    adj = new IntList[n];
    for (int i = 0; i < n; i++)
      adj[i] = new IntList();
    while (m-- > 0) {
      int i = in.nextInt() - 1, j = in.nextInt() - 1;
      adj[i].add(j);
      adj[j].add(i);
    }
    vis = new boolean[n];
    int res = 0;
    for (int i = 0; i < n; i++)
      res = Math.max(res, dfs(i));
    System.out.println(res);
  }
}
