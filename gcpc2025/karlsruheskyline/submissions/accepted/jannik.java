import java.util.*;
import java.util.stream.*;

public class jannik {
  static List<Integer> solve(int n, int a, int b) {
    return Stream.of(
      IntStream.range(n - a + 1, n).boxed(),
      IntStream.rangeClosed(1, n - a - b + 1).boxed(),
      IntStream.of(n).boxed(),
      IntStream.rangeClosed(a - n, a + b - n - 2).map(i -> -i).boxed()
    ).flatMap(i -> i).toList();
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt(), a = in.nextInt(), b = in.nextInt();
    if (a + b - 1 > n || Math.max(a, b) == 1) {
      System.out.println("no");
      return;
    }
    System.out.println("yes");
    List<Integer> s;
    if (a >= b)
      s = solve(n, a, b);
    else {
      s = new ArrayList<>(solve(n, b, a));
      Collections.reverse(s);
    }
    s.forEach(i -> System.out.print(i + " "));
  }
}
