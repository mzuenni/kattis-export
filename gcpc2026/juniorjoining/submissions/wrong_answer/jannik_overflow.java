import java.util.*;

public class jannik_overflow {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    final int MAXC = 1 << 20;
    ArrayList<int[]> cities[] = new ArrayList[MAXC];
    for (int i = 0; i < cities.length; i++)
      cities[i] = new ArrayList<>();
    for (int i = 0; i < 2 * n; i++) {
      int a = in.nextInt(), b = in.nextInt(), c = in.nextInt();
      cities[c].add(new int[] { a, b });
    }
    PriorityQueue<Integer> gain_a = new PriorityQueue<>();
    PriorityQueue<Integer> gain_b = new PriorityQueue<>();
    long score = 0;
    for (int c = MAXC; c-- > 0; ) {
      cities[c].sort((l, r) -> { return (r[1] - r[0]) - (l[1] - l[0]); });
      int i;
      for (i = 0; i < cities[c].size() / 2; i++) {
        int[] x = cities[c].get(i);
        score += x[1];
        gain_a.add(x[1] - x[0] + c);
      }
      if (cities[c].size() % 2 != 0) {
        cities[0].add(cities[c].get(i));
        cities[c].remove(i);
      }
      for (; i < cities[c].size(); i++) {
        int[] x = cities[c].get(i);
        score += x[0];
        gain_b.add(x[0] - x[1] + c);
      }
      score += cities[c].size() / 2 * c;
    }
    while (!gain_a.isEmpty() && !gain_b.isEmpty()) {
      int d = gain_a.poll() + gain_b.poll();
      if (d >= 0)
        break;
      score -= d;
    }
    System.out.println(score);
  }
}
