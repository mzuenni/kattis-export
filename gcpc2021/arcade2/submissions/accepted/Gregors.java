import java.util.Scanner;
public class Gregors {
    public static long naive(long n)
    {
        if (n == 1 || n == 3) return 1;
        for (int i = 0; i < 63; ++i)
            for (int j = i; j < 63; ++j)
                if (0L + (1L << i) + (1L << j) + 1 == n)
                    return (1L << i) + 1;
        return -1;
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        long n = s.nextLong();
        long ans = naive(n);
        if (ans == -1) System.out.println("impossible");
        else System.out.println(ans);
    }
}