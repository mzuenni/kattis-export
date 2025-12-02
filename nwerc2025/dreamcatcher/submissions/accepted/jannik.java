import java.util.*;
import java.math.BigInteger;

public class jannik {
  public static void main(String[] args) {
    int n = new Scanner(System.in).nextInt();
    int k = n / 2;
    while (!BigInteger.valueOf(n).gcd(BigInteger.valueOf(k)).equals(BigInteger.ONE))
      k--;
    System.out.println(k);
  }
}
