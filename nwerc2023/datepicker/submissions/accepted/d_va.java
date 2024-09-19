import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

public class d_va {
    public static void main(String[] args) {
        new d_va().run();
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public void solve() throws IOException {
        char[][] map = new char[7][24];
        for (int i = 0; i < map.length; i++) {
            map[i] = nextToken().toCharArray();
        }

        int[] masks = new int[24];
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 7; j++) {
                masks[i] += (map[j][i] == '.' ? 1 : 0) << j;
            }
        }

        int d = nextInt();
        int h = nextInt();
        double ans = 0;
        for (int days = 0; days < 1 << 7; days++) {
            if (Integer.bitCount(days) < d) {
                continue;
            }
            int[] inter = new int[24];
            for (int hour = 0; hour < 24; hour++) {
                inter[hour] = Integer.bitCount(days & masks[hour]);
            }
            Arrays.sort(inter);

            int th = 0;
            int sum = 0;
            for (int hour = inter.length - 1; hour >= 0; hour--) {
                th++;
                sum += inter[hour];
                if (th >= h) {
                    ans = Math.max(ans, 1. * sum / (Integer.bitCount(days) * th));
                }
            }
        }

        out.println(ans);
    }

    public void run() {
        try {
            br = new BufferedReader(new InputStreamReader(System.in));
            out = new PrintWriter(System.out);

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}