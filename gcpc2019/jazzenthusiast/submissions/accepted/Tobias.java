import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class Tobias {
  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      String[] data = reader.readLine().split(" ");
      int n = Integer.parseInt(data[0]);
      int c = Integer.parseInt(data[1]);
      int s = -c * (n - 1);

      for (int i = 0; i < n; i++) {
        String[] line = reader.readLine().split(":");
        int m = Integer.parseInt(line[0]);
        int ss = Integer.parseInt(line[1]);
        s += 60 * m + ss;
      }
      System.out.printf("%02d:%02d:%02d", s / 3600, (s / 60) % 60, s % 60);
    }
  }
}
