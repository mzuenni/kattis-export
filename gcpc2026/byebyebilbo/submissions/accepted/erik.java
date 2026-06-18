import java.util.*;
import java.io.*;

public class erik {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());

        int[] p = new int[n];
        int[] d = new int[n];
        List<Integer> s = new ArrayList<>();

        st = new StringTokenizer(br.readLine());
        for (int i = 1; i < n; i++) {
            p[i] = Integer.parseInt(st.nextToken()) - 1;
        }

        s.add(0);
        for (int i = n - 1; i > 0; i--) {
            if (d[i] == k - 1)
                s.add(i);
            else
                d[p[i]] = Math.max(d[p[i]], d[i] + 1);
        }

        int m = s.size();
        StringBuilder sb = new StringBuilder();
        sb.append(m).append("\n");
        for (int i = 0; i < m; i++) {
            sb.append(s.get(i) + 1);
            sb.append(i + 1 == m ? "\n" : " ");
        }
        System.out.print(sb);
    }
}