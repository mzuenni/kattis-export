import java.util.*;
public class erik {
    static int N = 28, M = 13, C = 4100;
    static int[][] a = new int[N][2];
    static HashMap<Integer, int[]> vis[] = new HashMap[(2 * C + 1) * M];
    static void finish(int x, int y) {
        System.out.println("no");
        for (int msk: new int[]{x, y}) {
            System.out.print(Integer.bitCount(msk));
            for (int i = 0; i < N; i++)
                if ((msk >> i & 1) == 1)
                    System.out.print(" " + (i + 1));
            System.out.println();
        }
        System.exit(0);
    }
    static void dfs(int x, int y, int m, boolean f, int mskL, int mskR) {
        if (x == 0 && y == 0) finish(mskL, mskR);
        if (m < 0 && !f) {
            vis[x + M * C].put(y, new int[]{mskL, mskR});
            return;
        }
        if (m < M && f) {
            for (int s: new int[]{-1, 1}) {
                int i = s * x + M * C;
                if (0 <= i && i < (2 * C + 1) * M) {
                    int[] tmp = vis[i].get(s * y);
                    if (tmp == null)
                        continue;
                    if (s == -1)
                        tmp = new int[]{tmp[1], tmp[0]};
                    finish(mskL | tmp[1], mskR | tmp[0]);
                }
            }
            return;
        }
        dfs(x, y, m - 1, f, mskL, mskR);
        dfs(x + a[m][0], y + a[m][1], m - 1, f, mskL | (1 << m), mskR);
        dfs(x - a[m][0], y - a[m][1], m - 1, f, mskL, mskR | (1 << m));
    }
    public static void main(String[] args) {
        for (int i = 0; i < (2 * C + 1) * M; i++)
            vis[i] = new HashMap<Integer, int[]>();
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        n = Math.min(n, N);
        for (int i = 0; i < n; i++) {
            a[i][1] = in.nextInt();
            a[i][0] = in.nextInt();
            dfs(a[i][0], a[i][1], i - 1, i >= M, 1 << i, 0);
        }
        System.out.println("yes");
    }
}
