import java.util.*;

public class jannik {
  static String[] aa = {
      "4 4\n#.#.\nO#O#\n#.#.\nO#O#\n", // 1
      "4 4\nO##.\n#.O#\n#.#.\nO#O#\n", // 2
      "4 4\nO##O\n#..#\n#.#.\nO#O#\n", // 3
      "", "",
      "6 6\nO#O#O#\n#.#.#.\n#...O#\nO#.##.\n..#O#.\n..O#..\n", // 6
      "6 6\nO#O##O\n#.#..#\n#...O#\nO#.##.\n..#O#.\n..O#..\n", // 7
      "", "", "",
      "6 6\nO##O#O\n#..#.#\nO#...#\n#...#O\n#.#.O#\nO#O##.\n", // 11
  };

  public static void main(String[] args) {
    int a = new Scanner(System.in).nextInt();
    if (a < 4 || a == 6 || a == 7 || a == 11) {
      System.out.println(aa[a - 1]);
      return;
    }
    int w = 0, h = 0, f = -1;
    outer: for (w = 3; w <= 50; w++)
      for (h = 2; h <= 50; h++) {
        f = a - 4 * (w - 2) * (h - 2);
        if (f >= 0 && f <= h - 2)
          break outer;
      }
    System.out.println(h * 2 + " " + w * 2);
    System.out.println(".#".repeat(w));
    System.out.println("#O".repeat(w));
    for (int i = 0; i < h - 2; i++) {
      System.out.println(".#" + "..".repeat(w - 2) + (i < f ? ".#" : "#."));
      System.out.println("#O" + "..".repeat(w - 2) + (i < f ? "#O" : "O#"));
    }
    System.out.println("#O".repeat(w));
    System.out.println(".#".repeat(w));
  }
}
