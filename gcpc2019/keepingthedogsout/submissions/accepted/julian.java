import java.util.Scanner;

public class julian {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int n = s.nextInt();

        long[] cnt = new long[n + 1];
        for (int i = 0; i <= n; ++i) cnt[i] = s.nextLong();

        long area = 0;
        for (int i = 0; i <= n; ++i) {
            area += (1L << i) * (1L << i) * cnt[i];
        }

        for (long i = 1; i * i <= area; ++i) {
            if (area % i != 0) continue;

            long current_area = 0;
            boolean possible = true;
            for (int k = n; k >= 0; --k) {
                long border_length = 1L << k;
                current_area += border_length * border_length * cnt[k];
                long a = (i / border_length) * border_length;
                long b = ((area / i) / border_length) * border_length;
                if (a * b < current_area) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                System.out.println(i + " " + area / i);
                return;
            }
        }

        System.out.println("impossible");
    }
}
