import java.io.*;
import java.util.*;

import static java.lang.Math.*;

public class PaulTranscribed {
    public static void main(String[] args) throws IOException {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            new PaulTranscribed().run(new Scanner(reader));
        }
    }

    int N = 2222, undefined = 0x42424242;
    int M = 1;
    List<List<Integer>> expo = new ArrayList<>();

    int[][] comp = new int[N][N];
    int compare(int a, int b) {
        if (a == b) return 0;
        if (comp[a][b] != undefined) return comp[a][b];
        int m = expo.get(a).size(), n = expo.get(b).size();
        for (int k = 0; k < min(m, n); k++) {
            int cur = compare(expo.get(a).get(k), expo.get(b).get(k));
            if (cur != 0) return comp[a][b] = cur;
        }
        return comp[a][b] = (m != n ? (m > n ? 1 : -1) : 0);
    }

    String remap(int c){
        if(c == -1)return "<";
        if(c == 0)return "=";
        return ">";
    }

    public void run(Scanner sc) throws IOException {
        int n = sc.nextInt(), m = sc.nextInt();
        for (int[] ints : comp) {
            Arrays.fill(ints, undefined);
        }
        for (int i = 0; i < N; i++) {
            expo.add(new ArrayList<>());
        }

        int[] v = new int[n];
        while (m-- > 0) {
            String c = sc.next();
            int i = sc.nextInt() - 1, j = sc.nextInt() - 1;
            if (c.equals("!")) {
                expo.set(M, new ArrayList<>(expo.get(v[i])));
                List<Integer> w = expo.get(M);
                w.add(v[j]);
                w.sort((a, b) -> -compare(a, b));
                v[i] = M++;
            } else {
                System.out.println(remap(compare(v[i], v[j])));
            }
        }
    }
}
