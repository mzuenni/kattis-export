import java.io.*;
import java.nio.charset.StandardCharsets;

public class Tobias {
    private static final StringBuilder builder = new StringBuilder(8096);
    private static void createTreeBalanced(int start, int end) {
        if (end < start) {
            return;
        }
        int mid = (start + end) >>> 1;
        builder.append(mid).append(" ");
        createTreeBalanced(start, mid - 1);
        createTreeBalanced(mid + 1, end);
    }

    private static void createTree(int start, int end, int depth) {
        if (depth <= 0) {
            createTreeBalanced(start, end);
        } else {
            int mid = (start + end) >>> 1;
            int first = Math.max(start, mid - depth);
            for (int i = first; i <= mid; i++) {
                builder.append(i).append(" ");
            }
            createTreeBalanced(start, first - 1);
            createTree(mid + 1, end, depth - mid + first);
        }
    }

    public static void main(String... args) throws IOException {
        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
            String[] data = reader.readLine().split(" ");
            int n = Integer.parseInt(data[0]);
            int k = Integer.parseInt(data[1]);

            for (int i = n; i > 0; i /= 2) {
                k--;
            }
            if (k < 0) {
                System.out.println("impossible");
            } else {
                createTree(1, n, k);
                System.out.println(builder.toString());
            }
        }
    }
}
