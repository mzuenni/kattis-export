import java.math.*;
import java.util.*;

public class PaulDouble {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        long[] x = new long[n];
        long[] y = new long[n];
        long[] xSum = new long[n+1];
        long[] ySum = new long[n+1];
        for (int i = 0; i < n; i++) {
            x[i] = sc.nextInt();
            y[i] = sc.nextInt();
            xSum[i+1] = xSum[i] + x[i];
            ySum[i+1] = ySum[i] + y[i];
        }

        double sum = 0;
        long area = 0;
        for (int i = 0; i < n; i++) {
            long x1 = i*x[i] - xSum[i];
            long y1 = i*y[i] - ySum[i];
            long x2 = xSum[n] - xSum[i+1] - (n-1-i)*x[i];
            long y2 = ySum[n] - ySum[i+1] - (n-1-i)*y[i];
            sum += (double) x1 * y2 - (double) x2 * y1;
            area += x[i]*y[(i+1)%n] - x[(i+1)%n]*y[i];
        }

        System.out.format("%.20f\n", sum / area);
    }
}
