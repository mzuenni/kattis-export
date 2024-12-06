import java.util.*;

public class Paul {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();

        int[] x = new int[n];
        int[] y = new int[n];
        int[] h = new int[n];
        for (int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
            h[i] = sc.nextInt();
        }

        for (int i = 0; i < n; i++) {
            int r = h[i];
            for (int j = 0; j < n; j++) {
                if (h[i] < h[j]) {
                    r = Math.min(r, (int) Math.hypot(x[j]-x[i], y[j]-y[i]));
                }
            }
            System.out.println(r);
        }
    }
}
