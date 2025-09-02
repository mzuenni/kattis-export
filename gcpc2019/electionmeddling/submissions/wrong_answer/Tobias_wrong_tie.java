import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class Tobias_wrong_tie {
  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(
      new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      String[] data = reader.readLine().split(" ");
      int w = Integer.parseInt(data[0]);
      int p = Integer.parseInt(data[1]);
      int[] bribes = new int[w];

      for (int i = 0; i < w; i++) {
        int[] l = Arrays.stream(reader.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int v0 = l[0];

        for (int j = 1; j < l.length; j++) {
          if (v0 < l[j]) {
            int c = (l[j] - v0 + 1) / 2;
            v0 += c;
              bribes[i] += c;
          }
        }
      }
      Arrays.sort(bribes);
      int sum = 0;
      for (int i = 0; i < (w / 2 + 1); i++) {
        sum += bribes[i];
      }
      System.out.println(sum);
    }
  }
}
