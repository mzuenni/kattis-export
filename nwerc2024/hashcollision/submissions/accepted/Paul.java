import java.math.*;
import java.util.*;

public class Paul {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        Random rng = new Random(123);

        int s = 0, g = 0, x = 1 + rng.nextInt(n);
        Map<Integer,Integer> seen = new HashMap<Integer,Integer>();
        while (g == 0 || g > n) {
            seen.put(x, s);
            int k = s > n ? 1 : (int) Math.sqrt(n);
            System.out.println("? " + k + " " + x);
            System.out.flush();
            x = sc.nextInt();
            s += k;
            var t = seen.get(x);
            if (t != null) {
                g = BigInteger.valueOf(g).gcd(BigInteger.valueOf(s - t)).intValue();
            }
            seen.put(x, s);
        }

        int y = ((-x) % g + g) % g;
        if (y == 0) y += g;
        System.out.println("? " + y + " " + x);
        System.out.flush();

        int z = sc.nextInt();
        System.out.println("! " + x + " " + z);
    }
}
