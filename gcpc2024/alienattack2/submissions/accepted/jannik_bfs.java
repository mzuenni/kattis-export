import java.util.*;

public class jannik_bfs {
  static class IntList extends ArrayList<Integer> {}
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), m = in.nextInt();
    IntList[] adj = new IntList[n];
    for (int i = 0; i < n; i++)
      adj[i] = new IntList();
    while (m-- > 0) {
      int i = in.nextInt() - 1, j = in.nextInt() - 1;
      adj[i].add(j);
      adj[j].add(i);
    }
    boolean[] vis = new boolean[n];
    int res = 0;
    for (int i = 0; i < n; i++) {
      if (vis[i])
        continue;
      IntList st = new IntList();
      st.add(i);
      vis[i] = true;
      for (int j = 0; j < st.size(); j++)
        for (int k : adj[st.get(j)])
          if (!vis[k]) {
            vis[k] = true;
            st.add(k);
          }
      res = Math.max(res, st.size());
    }
    System.out.println(res);
  }
}
