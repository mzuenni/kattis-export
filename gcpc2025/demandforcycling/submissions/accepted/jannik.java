import java.util.*;

public class jannik {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int maxx = Integer.MIN_VALUE, minx = Integer.MAX_VALUE;
    int maxy = maxx, miny = minx;
    for (int n = in.nextInt(); n-- > 0;) {
      int x = in.nextInt(), y = in.nextInt();
      maxx = Math.max(maxx, x);
      minx = Math.min(minx, x);
      maxy = Math.max(maxy, y);
      miny = Math.min(miny, y);
    }
    System.out.println(4);
    System.out.println(maxx + " " + miny);
    System.out.println(maxx + " " + maxy);
    System.out.println(minx + " " + maxy);
    System.out.println(minx + " " + miny);
  }
}
