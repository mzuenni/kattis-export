import java.util.*;
import java.util.stream.IntStream;

public class takuki {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] p = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = sc.nextInt();
        }
        Arrays.sort(p);

        int sum = IntStream.of(p).sum();
        long ans = 0;
        long[] dp = new long[sum + 1];
        dp[0] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = sum; j >= p[i]; j--) {
                if (j > sum - j && (j - p[i]) <= sum - (j - p[i])) {
                    ans += dp[j - p[i]];
                }
                dp[j] += dp[j - p[i]];
            }
        }

        System.out.println(ans);
    }
}
