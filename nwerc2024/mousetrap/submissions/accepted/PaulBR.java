import java.io.*;
import java.math.*;
import java.util.*;

public class PaulBR {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());

        long[] x = new long[n];
        long[] y = new long[n];
        long[] xSum = new long[n+1];
        long[] ySum = new long[n+1];
        for (int i = 0; i < n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            x[i] = Integer.parseInt(st.nextToken());;
            y[i] = Integer.parseInt(st.nextToken());;
            xSum[i+1] = xSum[i] + x[i];
            ySum[i+1] = ySum[i] + y[i];
        }

        BigInteger sum = BigInteger.ZERO;
        long area = 0;
        for (int i = 0; i < n; i++) {
            long x1 = i*x[i] - xSum[i];
            long y1 = i*y[i] - ySum[i];
            long x2 = xSum[n] - xSum[i+1] - (n-1-i)*x[i];
            long y2 = ySum[n] - ySum[i+1] - (n-1-i)*y[i];
            sum = sum.add(BigInteger.valueOf(x1).multiply(BigInteger.valueOf(y2)));
            sum = sum.subtract(BigInteger.valueOf(x2).multiply(BigInteger.valueOf(y1)));
            area += x[i]*y[(i+1)%n] - x[(i+1)%n]*y[i];
        }

        System.out.format("%.20f\n", sum.doubleValue() / area);
    }
}
