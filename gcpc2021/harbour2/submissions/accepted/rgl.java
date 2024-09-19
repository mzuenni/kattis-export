import java.io.*;
import java.util.*;
import java.util.stream.*;

import static java.util.stream.Collectors.*;

public class rgl {
  private static long solve(int[] s1, int[] s2) {
    final int n = s1.length + s2.length;

    final Map<Integer, Integer> position = new HashMap<>();
    IntStream.range(0, s1.length).forEach(i -> position.put(s1[i], i));
    IntStream.range(0, s2.length).forEach(i -> position.put(s2[i], n-1-i));

    final int x0 = position.get(0);
    final int[] l = IntStream.range(-1, n-1).toArray();
    final int[] r = IntStream.range(+1, n+1).toArray();
    return
        (x0 == s1.length-1 || x0 == s1.length ? 1 : 0)
        + IntStream.range(1, n)
            .map(position::get)
            .filter(i -> {
              if (0 <= l[i] && l[i] < n) r[l[i]] = r[i];
              if (0 <= r[i] && r[i] < n) l[r[i]] = l[i];
              return (l[i] == x0 || r[i] == x0);
            })
            .count();
  }

  public static void main(String[] args) throws IOException {
    final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    final int[] nmo = readArray(br);
    System.out.println(solve(readArray(br), readArray(br)));
  }

  private static int[] readArray(BufferedReader br) throws IOException {
    return Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
  }
}
