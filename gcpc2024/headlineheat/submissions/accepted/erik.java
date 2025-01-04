import java.io.*;
import java.util.*;

public class erik {
    static final int N = 3 * 100000 + 5;
    static final int C = 27;
    static final int K = 3;
    static final long[] P = {1000000007, 1000000009, 1000000021};
    static final long[] B = {123456789, 987654321, 543212345};

    static int M = 1;
    static int[] lnk = new int[N];
    static int[] val = new int[N];
    static int[] par = new int[N];
    static long[][] hash = new long[N][K];
    static int[][] go = new int[N][C];

    static {
        Arrays.fill(lnk, -1);
        Arrays.fill(par, -1);
    }

    public static int getLink(int k) {
        if (lnk[k] == -1) {
            lnk[k] = (k == 0 || par[k] == 0) ? 0 : walk(getLink(par[k]), val[k]);
        }
        return lnk[k];
    }

    public static int walk(int k, int c) {
        if (go[k][c] == 0) {
            return (k == 0) ? 0 : walk(getLink(k), c);
        }
        return go[k][c];
    }

    public static boolean match(String s) {
        int k = 0;
        long[] res = new long[K];
        for (char c : s.toCharArray()) {
            k = walk(k, (c == ' ') ? 0 : c - 'a' + 1);
            for (int i = 0; i < K; i++) {
                res[i] += hash[k][i] - P[i] * (res[i] + hash[k][i] >= P[i] ? 1 : 0);
            }
        }
        return Arrays.equals(res, new long[K]);
    }

    public static int insert(String s) {
        int u = 0;
        for (char c : s.toCharArray()) {
            int ch = (c == ' ') ? 0 : c - 'a' + 1;
            if (go[u][ch] == 0) {
                go[u][ch] = M;
                par[M] = u;
                val[M] = ch;
                M++;
            }
            u = go[u][ch];
        }
        return u;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        int[] fin = new int[n];
        long[] cur = new long[K];
        Arrays.fill(cur, 1);

        for (int i = 0; i < n; i++) {
            fin[i] = insert(br.readLine().trim());
        }

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int a = fin[Integer.parseInt(st.nextToken()) - 1];
            int b = fin[Integer.parseInt(st.nextToken()) - 1];
            for (int j = 0; j < K; j++) {
                cur[j] = cur[j] * B[j] % P[j];
                hash[a][j] -= cur[j] - P[j] * (hash[a][j] - cur[j] < 0 ? 1 : 0);
                hash[b][j] += cur[j] - P[j] * (hash[b][j] + cur[j] >= P[j] ? 1 : 0);
            }
        }

        for (int i = 0; i < k; i++) {
            if (match(br.readLine().trim())) {
                out.println("yes");
            } else {
                out.println("no");
            }
        }

        out.close();
    }
}
