import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

class aalex {
  public static void main(String[] args) throws IOException {
    BufferedReader reader =
        new BufferedReader(new InputStreamReader(System.in));
    String[] nmxy = reader.readLine().split(" ");
    int n = Integer.parseInt(nmxy[0]);
    int m = Integer.parseInt(nmxy[1]);
    int x = Integer.parseInt(nmxy[2]);
    int y = Integer.parseInt(nmxy[3]);
    int[] a = Arrays.stream(reader.readLine().split(" "))
        .mapToInt(Integer::parseInt)
        .toArray();
    Arrays.sort(a);
    int[] b = Arrays.stream(reader.readLine().split(" "))
        .mapToInt(Integer::parseInt)
        .toArray();
    Arrays.sort(b);
    
    int lo = -1, hi = n + 1;
    while (hi - lo > 1) {
      int mid = (lo + hi) / 2;

      int i = 0, j = 0, k = 0;
      while (i < m) {
        while (j < n && (b[i] > a[j] || k >= (j < mid ? y : x))) {
          ++j;
          k = 0;
        }
        if (j >= n) break;
        ++k;
        ++i;
      }

      if (i == m) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    if (lo < 0) {
      System.out.println("impossible");
    } else {
      System.out.println(lo);
    }
  }
}
