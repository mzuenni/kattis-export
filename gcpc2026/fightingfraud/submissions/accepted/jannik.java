import java.util.*;

public class jannik {
  static void fail() {
    System.out.println("no");
    System.exit(0);
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    HashSet<String> seen = new HashSet<>(), s = new HashSet<>();
    for (int n = in.nextInt(); n-- > 0; ) {
      String a = in.next(), b = in.next();
      if (a.equals("pickup")) {
        if (seen.contains(b))
          fail();
        seen.add(b);
        s.add(b);
      } else {
        if (!s.remove(b))
          fail();
      }
    }
    System.out.println(s.isEmpty() ? "yes" : "no");
  }
}
