import java.util.*;

public class jannik {
  static class IntList extends ArrayList<Integer> {
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), d = in.nextInt();
    IntList pos[] = new IntList[n + 1];
    for (int i = 0; i <= n; i++)
      pos[i] = new IntList();
    for (int i = 0; i < n; i++) {
      int p = in.nextInt();
      pos[p].add(i);
    }

    loop: for (int mex = 0;; mex++) {
      IntList p = pos[mex];
      for (int i = 0, next = 0; i < p.size();) {
        int j = i + 1;
        while (j < p.size() && p.get(j - 1) + d >= p.get(j))
          j++;
        if (next > p.get(i) || p.get(j - 1) - p.get(i) >= d)
          continue loop;
        next = Math.max(next, Math.min(p.get(i), p.get(j - 1) - d + 1)) + 2 * d;
        i = j;
      }
      System.out.println(mex);
      break;
    }
  }
}
