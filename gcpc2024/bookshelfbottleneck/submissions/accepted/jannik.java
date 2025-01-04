import java.util.*;
public class jannik {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    long h = in.nextLong(), res = 0;
    boolean ok = true;
    for (int i = 0; i < n; i++) {
      long x = in.nextLong(), y = in.nextLong(), z = in.nextLong();
      long tmp = (long) 1.1e9;
      if (Math.min(x,y) <= h)
        tmp = z;
      if (y < tmp && Math.min(x,z) <= h)
        tmp = y;
      if (x < tmp && Math.min(y,z) <= h)
        tmp = x;
      if (tmp > 1e9)
        ok = false;
      res += tmp;
    }
    System.out.println(ok ? res : "impossible");
  }
}
