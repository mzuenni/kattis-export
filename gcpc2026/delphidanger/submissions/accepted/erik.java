import java.util.*;
import java.io.*;

public class erik {
    static int[] par, col;
    static int[][] sz;
    static Set<Integer> vis = new HashSet<>();

    static int[] qry(int x) {
        if (x == par[x]) return new int[]{x, col[x]};
        int[] res = qry(par[x]);
        res[1] ^= col[x];
        return res;
    }

    static boolean join(int u, int v) {
        int[] rx = qry(u), ry = qry(v);
        u = rx[0]; v = ry[0];
        if (u == v) return rx[1] != ry[1];
        vis.add(u);
        vis.add(v);
        if (sz[u][0] + sz[u][1] > sz[v][0] + sz[v][1]) {
            int tmp = u; u = v; v = tmp;
        }
        par[u] = v;
        if (rx[1] != ry[1]) {
            int tmp = sz[u][0]; sz[u][0] = sz[u][1]; sz[u][1] = tmp;
        }
        sz[v][0] += sz[u][1];
        sz[v][1] += sz[u][0];
        col[u] = rx[1] ^ ry[1] ^ 1;
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        int[][] e = new int[m][3];
        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken()) - 1;
            int v = Integer.parseInt(st.nextToken()) - 1;
            int t = Integer.parseInt(st.nextToken());
            e[i] = new int[]{t, u, v};
        }

        Arrays.sort(e, (a, b) -> Integer.compare(b[0], a[0]));

        par = new int[n];
        col = new int[n];
        sz = new int[n][2];
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i][0] = 1;
        }

        long ans = 0;

        for (int i = 0, j = 0; i < m; i = j) {
            vis.clear();
            while (j < m && e[i][0] == e[j][0]) {
                e[j][1] = qry(e[j][1])[0];
                e[j][2] = qry(e[j][2])[0];
                j++;
            }
            for (int k = i; k < j; k++) {
                if (!join(e[k][1], e[k][2])) {
                    System.out.println("impossible");
                    return;
                }
            }
            for (int u : vis) {
                int[] dat = qry(u);
                if (u == dat[0]) {
                    ans += Math.min(sz[u][0], sz[u][1]);
                }
                int total = sz[u][0] + sz[u][1];
                sz[u][0] = total;
                sz[u][1] = 0;
                if (dat[1] != 0) {
                    int tmp = sz[u][0]; sz[u][0] = sz[u][1]; sz[u][1] = tmp;
                }
            }
        }

        System.out.println("possible");
        System.out.println(ans);
    }
}