import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class MarkusBufferedReader {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    int[] t = new int[1200000];
    int nn;

    void modify(int p, int value) {
        p += nn;
        for (t[p] = Math.max(t[p], value); p > 1; p >>= 1) {
            t [p >> 1] = Math.max(t[p], t[p ^ 1]);
        }
    }

    int query(int l, int r) {
        int res = 0;
        for (l += nn, r += nn; l < r; l >>= 1, r >>= 1) {
            if ((l & 1) != 0) {
                res = Math.max(res, t[l++]);
            }
            if ((r & 1) != 0) {
                res = Math.max(res, t[--r]);
            }
        }
        return res;
    }

    void solve() throws Exception {
		int n = Integer.valueOf(in.readLine());
        nn = n + 2;
		int[] a = new int[n];
		String[] ps = in.readLine().split(" ");
        for (int i = 0; i < n; i++) {
			a[i] = Integer.valueOf(ps[i]);
        }

        List<List<Integer>> right = new ArrayList<>(), down = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            right.add(new ArrayList<>());
            down.add(new ArrayList<>());
        }
        for (int i = 0; i < n; i++) {
            int l = i + 1;
            int r = a[i] - i - 1;
            if (r >= 0) {
                down.get(l).add(r);
            }

            l = a[i] - n + i;
            r = n - i;
            if (l >= 0) {
                right.get(l).add(r);
            }
        }

        for (int l = 0; l <= n; l++) {
            List<Integer> d = down.get(l);
            d.sort(Comparator.<Integer> naturalOrder().reversed());
            for (int r : d) {
                int best = query(0, r + 1);
                modify(r, best + 1);
            }

            List<Integer> ri = right.get(l);
            ri.sort(Comparator.naturalOrder());
            for (int r : ri) {
                int best = query(0, r);
                modify(r, best + 1);
            }
        }
        
        int ans = n - query(0, n + 1);
        System.out.println(ans);
    }

    public static void main(String[] args) throws Exception {
        new MarkusBufferedReader().solve();
    }
}
