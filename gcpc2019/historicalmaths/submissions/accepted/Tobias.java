import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Tobias {
  private static long[] multiply(long[] a, long[] b, long B) {
    long[] res = new long[a.length + b.length];
    for (int i = 0; i < a.length; i++) {
      for (int j = 0; j < b.length; j++) {
        res[i + j] += a[i] * b[j];
        if (res[i + j] >= B) {
          res[i + j + 1] += res[i + j] / B;
          res[i + j] %= B;
        }
      }
    }
    int i = res.length;
    while (res[i - 1] == 0) {
      i--;
    }
    return Arrays.copyOf(res, i);
  }

  private static boolean lessThan(long[] a, long[] b) {
    if (a.length != b.length) {
      return a.length < b.length;
    }
    for (int i = a.length - 1; i >= 0; i--) {
      if (a[i] != b[i]) {
        return a[i] < b[i];
      }
    }
    return false;
  }

  private static long[] readPoly(String[] data) {
    int n = Integer.parseInt(data[0]);
    long[] result = new long[n];
    for (int i = 0; i < n; i++) {
      result[n - i - 1] = Long.parseLong(data[i + 1]);
    }
    return result;
  }

  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(
        new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      long[] a = readPoly(reader.readLine().split(" "));
      long[] b = readPoly(reader.readLine().split(" "));
      long[] c = readPoly(reader.readLine().split(" "));

      long Bmin = 0;
      long Bmax = (long) 5e18;

      for (long[] arr : new long[][] {a, b, c}) {
        Bmin = Math.max(Bmin, Arrays.stream(arr).max().orElseThrow() + 1);
      }
      while (Bmin <= Bmax) {
        long B = (Bmin + Bmax) >>> 1;
        long[] ab = multiply(a, b, B);
        if (Arrays.equals(ab, c)) {
          System.out.println(B);
          System.exit(0);
        }
        if (lessThan(ab, c)) {
          Bmax = B - 1;
        } else {
          Bmin = B + 1;
        }
      }
      System.out.println("impossible");
    }
  }
}
