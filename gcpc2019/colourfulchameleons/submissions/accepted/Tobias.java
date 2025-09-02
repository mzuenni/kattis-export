import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Tobias {
    public static void main(String... args) throws IOException {
        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
            String[] data = reader.readLine().split(" ");
            int n = Integer.parseInt(data[0]);
            int t = Integer.parseInt(data[1]) - 1;
            int y = Integer.parseInt(data[2]);
            int[] x = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();

            int v = -1;
            int max = Integer.MIN_VALUE;
            long sum = 0;
            for (int i = 0; i < x.length; i++) {
                sum += x[i];
                if (i == t) {
                    continue;
                }
                int c = x[i] % (y + 1);
                if (v == -1) {
                    v = c;
                } else if (v != c) {
                    System.out.println("impossible");
                    System.exit(0);
                }
                if (max < x[i]) {
                    max = x[i];
                }
            }
            sum += (long) max * (y - n + 1);
            System.out.printf("%d %d", max, sum);
        }
    }
}
