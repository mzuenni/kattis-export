import java.util.*;

public class jannik {
  static int[] pa = new int[200200];
  static int ufind(int i) {
    return i == pa[i] ? i : (pa[i] = ufind(pa[i]));
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), m = in.nextInt();
    for (int i = 0; i < n; i++)
      pa[i] = i;
    while (m-- > 0) {
      int i = in.nextInt() - 1, j = in.nextInt() - 1;
      pa[ufind(i)] = ufind(j);
    }
    int[] num = new int[n];
    for (int i = 0; i < n; i++)
      num[ufind(i)]++;
    int res = 0;
    for (int i = 0; i < n; i++)
      if (res < num[i])
        res = num[i];
    System.out.println(res);
  }
}
