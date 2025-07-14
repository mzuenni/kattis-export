import java.util.*;

public class Paul {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int h = sc.nextInt();
        int w = sc.nextInt();

        int total = 0;
        String[] grid = new String[h];
        for (int i = 0; i < h; i++) {
            grid[i] = sc.next();
            total += grid[i].chars().filter(c -> c == '#').count();
        }

        for (int n = Math.min(h, w); n >= 1; n--) {
            if (total % (n*n) != 0) continue;
            boolean[][] mark = new boolean[h][w];
            boolean ok = true;
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    if (!mark[i][j] && grid[i].charAt(j) == '#') {
                        for (int ni = i; ni < i+n; ni++) {
                            for (int nj = j; nj < j+n; nj++) {
                                if (ni >= h || nj >= w || mark[ni][nj] || grid[ni].charAt(nj) == '.') {
                                    ok = false;
                                } else {
                                    mark[ni][nj] = true;
                                }
                            }
                        }
                    }
                }
            }
            if (ok) {
                System.out.println(n);
                return;
            }
        }
    }
}
