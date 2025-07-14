import java.util.*;

public class jannik {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    long t = in.nextLong();
    long a[] = new long[n];
    for (int i = 0; i < n; i++)
      a[i] = in.nextLong();
    for (int i = 0; i < n && t > 0; i += 2) {
      if (a[i] != 0) { // simulate
        long h = 1;
        for (int j = i; j < n; j++) {
          a[j]++;
          if (--h > 0) continue;
          if (a[j] == 1) break;
          h += a[j];
          a[j] = 0;
        }
        if (--t == 0) break;
      }
      a[i] = t % 2;
      t /= 2;
      if (i + 1 < n)
        a[i+1] += t;
    }
    for (int i = 0; i < n; i++)
      System.out.print(a[i] + " ");
  }
}
