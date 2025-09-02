import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class Tobias {
  private static int repetitions(String s) {
    if (s.length() < 2) {
      return s.length();
    }

    for (int i = 1; i <= s.length() / 2; i++) {
      if (s.length() % i != 0) {
        continue;
      }
      boolean isRepetition = true;
      for (int j = i; j < s.length(); j++) {
        if (s.charAt(j % i) != s.charAt(j)) {
          isRepetition = false;
          break;
        }
      }
      if (isRepetition) {
        return i;
      }
    }
    return s.length();
  }

  public static void main(String... args) throws IOException {
    try (BufferedReader reader = new BufferedReader(
        new InputStreamReader(System.in, StandardCharsets.UTF_8))) {
      int n = Integer.parseInt(reader.readLine());

      List<Integer> virus = new ArrayList<>(n);
      List<Integer> anti = new ArrayList<>(n);
      for (int i = 0; i < n; i++) {
        virus.add(repetitions(reader.readLine()));
      }
      Collections.sort(virus);
      for (int i = 0; i < n; i++) {
        anti.add(repetitions(reader.readLine()));
      }
      Collections.sort(anti);

      Iterator<Integer> virusIter = virus.iterator();
      Iterator<Integer> antiIter = anti.iterator();

      long score = 0L;
      for (int i = 0; i < n; i++) {
        long elementScore = (virusIter.next() - antiIter.next());
        score += elementScore * elementScore;
      }

      System.out.printf("%d", score);
    }
  }
}
