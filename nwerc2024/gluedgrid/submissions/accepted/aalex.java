import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

class aalex {
  final static char UNSEEN = '.';
  final static char BLOCKED = '#';
  final static char SEEN = ':';
  final static char CHECKING = '!';

  final static int DELTAS[][] = new int[][] {
    {-1, 0},
    {0, -1},
    {0, 1},
    {1, 0},
  };

  final int h, w;
  final char status[][];
  final int puzzle[][];

  final int distToRoot[][];
  final int backreach[][];
  final int altIndex[][];
  final int altStack[][];
  int stackLen;

  aalex(int h, int w, char status[][], int[][] puzzle) {
    this.h = h;
    this.w = w;
    this.status = status;
    this.puzzle = puzzle;

    distToRoot = new int[h][w];
    backreach = new int[h][w];
    altIndex = new int[h][w];
    altStack = new int[h * w][2];
    stackLen = 0;
  }

  void push(int x, int y, int d) {
    status[x][y] = SEEN;
    distToRoot[x][y] = backreach[x][y] = d;
    altStack[stackLen][0] = x;
    altStack[stackLen][1] = y;
    altIndex[x][y] = stackLen++;
  }

  boolean isEven(int a, int b) {
    for (int i = a; i < b; ++i) {
      status[altStack[i][0]][altStack[i][1]] = CHECKING;
    }

    boolean even = true;
    for (int i = 0; i < b; ++i) {
      int x = altStack[i][0];
      int y = altStack[i][1];
      if (status[x][y] != CHECKING) continue;
      do {
        if (status[x][y] != CHECKING) return false;
        status[x][y] = SEEN;
        even = !even;
        int p = puzzle[x][y] - 1;
        x = p / w;
        y = p % w;
      } while (x != altStack[i][0] || y != altStack[i][1]);
      even = !even;
    }
    return even;
  }

  boolean depthFirstSearch(int x, int y, int px, int py) {
    for (int i = 0; i < DELTAS.length; ++i) {
      int x2 = x + DELTAS[i][0];
      int y2 = y + DELTAS[i][1];

      if (x2 < 0 || h <= x2) continue;
      if (y2 < 0 || w <= y2) continue;
      if (x2 == px && y2 == py) continue;
      if (status[x2][y2] == BLOCKED) continue;

      if (status[x2][y2] == SEEN) {
        if (backreach[x][y] > distToRoot[x2][y2]) {
          backreach[x][y] = distToRoot[x2][y2];
        }
        continue;
      }

      push(x2, y2, distToRoot[x][y] + 1);
      if (!depthFirstSearch(x2, y2, x, y)) return false;
      if (backreach[x2][y2] >= distToRoot[x][y]) {
        if (!isEven(altIndex[x2][y2], stackLen)) return false;
        stackLen = altIndex[x2][y2];
      }

      if (backreach[x][y] > backreach[x2][y2]) {
        backreach[x][y] = backreach[x2][y2];
      }
    }
    return true;
  }

  boolean isSolvable() {
    push(h - 1, w - 1, 0);
    return depthFirstSearch(h - 1, w - 1, -1, -1);
  }

  public static void main(String[] args) throws IOException {
    BufferedReader reader = 
      new BufferedReader(new InputStreamReader(System.in));

    String[] hw = reader.readLine().split(" ");
    int h = Integer.parseInt(hw[0]);
    int w = Integer.parseInt(hw[1]);

    char[][] status = new char[h][w];
    for (int i = 0; i < h; ++i) {
      status[i] = reader.readLine().toCharArray();
    }
    
    int[][] puzzle = new int[h][w];
    for (int i = 0; i < h; ++i) {
      puzzle[i] = Arrays.stream(reader.readLine().split(" "))
          .mapToInt(Integer::parseInt)
          .toArray();
    }

    boolean result = (new aalex(h, w, status, puzzle)).isSolvable();
    System.out.println(result ? "possible" : "impossible");
  }
}
